#include "Animation/Enemy_Animinstance.h"
#include "Characters/Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemy_Animinstance::NativeInitializeAnimation()
{
	//需要调用父类的函数，否则会导致动画蓝图无法获取角色对象
	Super::NativeInitializeAnimation();
	Enemy = Cast<AEnemy>(TryGetPawnOwner());
	if (Enemy) {
		CharacterMovement = Enemy->GetCharacterMovement();
	}
}

void UEnemy_Animinstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (CharacterMovement) {
		Speed = CharacterMovement->Velocity.Size2D();
	}
}
