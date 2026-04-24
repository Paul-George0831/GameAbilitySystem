#include "Characters/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Controller/DefaultPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MikuPlayerState.h"
#include "UI/HUD/MikuHUD.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm->SetupAttachment(GetRootComponent());
	Camera->SetupAttachment(SpringArm);

	//将旋转朝向移动，设置转向速度
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	
	//角色生成自动吸附到地面
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//禁用控制器带动旋转，也就是防止相机能控制角色转向
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//服务器初始化ASC和属性集
	InitAbilityActorInfo();
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//客户端初始化ASC和属性集
	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	AMikuPlayerState* MikuPlayerState = GetPlayerState<AMikuPlayerState>();//先获取到一个APlayerState，然后强转为AMikuPlayerState
	check(MikuPlayerState);
	MikuPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MikuPlayerState, this);//owner负责持久化数据，持有技能。AvatarActor负责角色位置，视觉表现
	AbilitySystemComponent = MikuPlayerState->GetAbilitySystemComponent();
	AttributeSet = MikuPlayerState->GetAttributeSet();
	
	//这里不能用断言，由于客户端只存在一个控制器，但存在多个character，如果这里是断言，其他character如果执行这段代码，就一定拿不到控制器，那么游戏就会立马崩溃
	if (ADefaultPlayerController* MikuPlayerController = GetController<ADefaultPlayerController>())
	{
		if (AMikuHUD* MikuHUD = MikuPlayerController->GetHUD<AMikuHUD>())
		{
			MikuHUD->InitOverlay(MikuPlayerController,MikuPlayerState,AbilitySystemComponent, AttributeSet);
		}
	}
}
