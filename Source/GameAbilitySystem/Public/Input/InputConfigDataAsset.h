// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputConfigDataAsset.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FAuraInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GameplayTag = FGameplayTag();
};

UCLASS()
class GAMEABILITYSYSTEM_API UInputConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& GameplayTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FAuraInputAction> AuraInputActions;
};
