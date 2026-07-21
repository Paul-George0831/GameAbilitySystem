#include "Animation/Enemy_Animinstance.h"
#include "Characters/Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemy_Animinstance::NativeInitializeAnimation()
{
	//��Ҫ���ø���ĺ���������ᵼ�¶�����ͼ�޷���ȡ��ɫ����
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
		CanMove = Speed > 0.f;
	}
}
