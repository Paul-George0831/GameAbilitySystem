// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Miku_Animinstance.h"
#include "Characters/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMiku_Animinstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	PlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (PlayerCharacter) {
		CharacterMovement = PlayerCharacter->GetCharacterMovement();
	}
}

void UMiku_Animinstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (CharacterMovement) {
		Speed = CharacterMovement->Velocity.Size2D();
		CanMove = Speed > 0.f; 
	}
}