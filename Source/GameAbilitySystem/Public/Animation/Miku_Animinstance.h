// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Miku_Animinstance.generated.h"

class APlayerCharacter;
class UCharacterMovementComponent;

UCLASS()
class GAMEABILITYSYSTEM_API UMiku_Animinstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	APlayerCharacter* PlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UCharacterMovementComponent* CharacterMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool CanMove;
};
