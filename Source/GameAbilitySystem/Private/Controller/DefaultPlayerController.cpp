#include "Controller/DefaultPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "Interfaces/HighlightInterface.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystem/GASAbilitySystemComponentBase.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/SplineComponent.h"
#include "Input/AuraEnhancedInputComponent.h"

ADefaultPlayerController::ADefaultPlayerController()
{
	//启用网络复制
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("SplineComponent");
	
}

void ADefaultPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControllerPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControllerPawn->AddMovementInput(Direction);
		
		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void ADefaultPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//鼠标光标追踪，显示高亮目标
	CursorTrace();
	
	AutoRun();
}

void ADefaultPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;//如果没检测到物体就直接返回
	LastHighLightedActor = CurHighLightActor;
	CurHighLightActor = Cast<IHighlightInterface>(CursorHit.GetActor());
	if (CurHighLightActor != LastHighLightedActor)
	{
		if (LastHighLightedActor) LastHighLightedActor->UnHighlight();
		if (CurHighLightActor) CurHighLightActor->Highlight();
	}
}

UGASAbilitySystemComponentBase* ADefaultPlayerController::GetASC()	
{
	if (!_GASASC)
	{
		_GASASC = Cast<UGASAbilitySystemComponentBase>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return _GASASC;
}

void ADefaultPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = CurHighLightActor != nullptr;//如果当前鼠标悬停的地方是角色，CurHighLightActor就不为空，返回true
		bAutoRunning = false;
	}
}

void ADefaultPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))//如果按下不是鼠标左键，直接通知其被按下了
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	if (bTargeting)
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		APawn* ControllerPawn = GetPawn();
		if (FollowTime <= ShortThreshold && ControllerPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,ControllerPawn->GetActorLocation(),CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);//导航系统返回的路径点是世界坐标
					DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Cyan,false, 5.f);
				}
				if (NavPath->PathPoints.Num() > 0)
				{
					CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
					bAutoRunning = true;
				}
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void ADefaultPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))//如果按下不是鼠标左键，直接通知其被按下了
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}
	if (bTargeting)
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;
		if (APawn* ControllerPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
			ControllerPawn->AddMovementInput(WorldDirection);
		}
	}
}

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//只有在beginplay的时候，增强输入系统才已经被初始化成功，所以创建系统必须要到beginplay,绑定按键映射到setupinputcompoent
	check(DefaultPlayerContext);
	//创建增强输入本地子系统
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	//这里getlocalplayer只在客户端返回有效的ULocalplayer，在服务器上返回nullptr,如果这里使用check(subsystem)就必然会崩溃
	if (SubSystem)
	{
		SubSystem->AddMappingContext(DefaultPlayerContext, 0);
	}
	//显示鼠标光标
	bShowMouseCursor = true;
	//设置鼠标Icon
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputData;
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//设置鼠标不锁定在窗口内
	InputData.SetHideCursorDuringCapture(false);//当鼠标被捕获的时候隐藏光标(点击操作游戏的时候隐藏)
	SetInputMode(InputData);
}

void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//创建增强输入组件
	UAuraEnhancedInputComponent* EnhancedInputComponent = CastChecked<UAuraEnhancedInputComponent>(InputComponent);
	//绑定回调函数
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::Move);
	EnhancedInputComponent->BindAbilityActions(InputConfig, this, &ADefaultPlayerController::AbilityInputTagPressed,&ADefaultPlayerController::AbilityInputTagReleased, &ADefaultPlayerController::AbilityInputTagHeld);
}

void ADefaultPlayerController::Move(const FInputActionValue& Value)
{
	//FInputActionValue是一个2维向量
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);//目的：当前角色只对着朝向的前方水平行动，不能够让他看到天上的时候就对着天上走，yaw是绕z轴旋转，所以pitch和roll都不需要控制器的值，只需要一直设置为0

	//讲世界参考系变换到控制器参考系
	const FVector FwdDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//获取控制器控制的Pawn
	if (APawn* ControllerPawn = GetPawn<APawn>()) {
		//使控制器控制的pawn移动
		ControllerPawn->AddMovementInput(FwdDir, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RDir, InputAxisVector.X);
	}
}