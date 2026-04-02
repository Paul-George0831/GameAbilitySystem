#include "Controller/DefaultPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ADefaultPlayerController::ADefaultPlayerController()
{
	//启用网络复制？
	bReplicates = true;
}

void ADefaultPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(DefaultPlayerContext);
	//配置增强输入子系统
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(SubSystem);
	SubSystem->AddMappingContext(DefaultPlayerContext, 0);
	//设置启用鼠标捕获
	bShowMouseCursor = true;
	//虚幻有很多光标类型，使用EMouseCursor管理，这里使用默认光标
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputData;
	InputData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);//设置进行游戏的时候，鼠标是否能够移出窗口
	InputData.SetHideCursorDuringCapture(true);//当启用鼠标捕获到视口的时候，不要隐藏光标
	SetInputMode(InputData);
	//= 鼠标自由 + 显示 + 可点 UI + 不锁定窗口
}

void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//把当前组件强转为增强输入组件
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	//绑定增强输入组件到输入移动
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADefaultPlayerController::Move);
}

void ADefaultPlayerController::Move(const FInputActionValue& Value)
{
	//FInputActionValue是一个通用容器，需要转换值
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);

	//变换参考系到控制器，旋转矩阵
	const FVector FwdDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//获取控制器控制的Pawn
	if (APawn* ControllerPawn = GetPawn<APawn>()) {
		//添加移动输入
		ControllerPawn->AddMovementInput(FwdDir, InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RDir, InputAxisVector.X);
	}
	
}

