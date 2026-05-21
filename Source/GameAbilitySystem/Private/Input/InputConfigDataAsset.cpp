// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputConfigDataAsset.h"

const UInputAction* UInputConfigDataAsset::FindAbilityInputActionForTag(const FGameplayTag& GameplayTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& Aia : AuraInputActions)
	{
		if (GameplayTag == Aia.GameplayTag)
		{
			return Aia.InputAction;
		}
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilityInputAction[%s] is not Found, InputConfig is [%s]"), *GameplayTag.ToString(), *GetNameSafe(this));
	}
	return nullptr;
}
