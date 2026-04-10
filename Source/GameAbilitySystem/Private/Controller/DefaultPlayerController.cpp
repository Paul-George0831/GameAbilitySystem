#include "Controller/DefaultPlayerController.h"
#include "Interfaces/HighlightInterface.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ADefaultPlayerController::ADefaultPlayerController()
{
	//启用网络复制
	bReplicates = true;
}

void ADefaultPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	//鼠标光标追踪，显示高亮目标

	CursorTrace();
}

void ADefaultPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;//如果没检测到物体就直接返回
	
	LastHighLightedActor = CurHighLightActor;
	CurHighLightActor = Cast<IHighlightInterface>(CursorHit.GetActor());
	if (CurHighLightActor == LastHighLightedActor) {
		if (CurHighLightActor) {
			CurHighLightActor->Highlight();

		}
	}
	else {
		if(CurHighLightActor) {
			if (LastHighLightedActor) {//如果上次的Actor和当前Actor2个都有效，就要只标亮当前actor
				LastHighLightedActor->UnHighlight();
			}
			CurHighLightActor->Highlight();//无论是否上一个actor有效还是无效，都需要标亮当前actor
		}
		else {
			if(LastHighLightedActor) {//当前actor无效，鼠标移动到别的地方了，就要取消标亮上一个actor
				LastHighLightedActor->UnHighlight();
			}
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
	check(SubSystem);
	SubSystem->AddMappingContext(DefaultPlayerContext, 0);
	//显示鼠标光标
	bShowMouseCursor = true;
	//设置鼠标Icon
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputData;
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//设置鼠标不锁定在窗口内
	InputData.SetHideCursorDuringCapture(true);//当鼠标被捕获的时候隐藏光标(点击操作游戏的时候隐藏)
	SetInputMode(InputData);
}

void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//创建增强输入组件
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	//绑定回调函数
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::Move);
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