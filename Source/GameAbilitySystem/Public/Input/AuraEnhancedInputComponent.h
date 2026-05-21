// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Input/InputConfigDataAsset.h"
#include "AuraEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEABILITYSYSTEM_API UAuraEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UInputConfigDataAsset* InputConfig, UserClass Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAuraEnhancedInputComponent::BindAbilityActions(const UInputConfigDataAsset* InputConfig, UserClass Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	for (const FAuraInputAction& Aia : InputConfig->AuraInputActions)
	{
		if (!Aia.InputAction || !Aia.GameplayTag.IsValid()) continue;
		if (PressedFunc)
		{
			BindAction(Aia.InputAction, ETriggerEvent::Started, Object, PressedFunc, Aia.GameplayTag);
		}
		if (ReleasedFunc)
		{
			BindAction(Aia.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Aia.GameplayTag);
		}
		if (HeldFunc)
		{
			BindAction(Aia.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Aia.GameplayTag);
		}                                                                                                                                                                     
	}
}
