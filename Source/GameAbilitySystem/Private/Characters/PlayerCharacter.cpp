#include "Characters/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MikuPlayerState.h"

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
	//记得设置gamemode的playerstate为创建的playerstate,否则如果plaerstate不是AMikustate类之外的类型，就会访问到空指针报错
	AMikuPlayerState* MikuPlayerState = GetPlayerState<AMikuPlayerState>();
	check(MikuPlayerState);
	MikuPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MikuPlayerState, this);
	AbilitySystemComponent = MikuPlayerState->GetAbilitySystemComponent();
	AttributeSet = MikuPlayerState->GetAttributeSet();
}
