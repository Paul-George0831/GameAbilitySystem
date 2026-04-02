#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Enemy_Animinstance.generated.h"

class AEnemy;
class UCharacterMovementComponent;

UCLASS()
class GAMEABILITYSYSTEM_API UEnemy_Animinstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	AEnemy* Enemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;
};
