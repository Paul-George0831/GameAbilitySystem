// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEABILITYSYSTEM_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()	

public:
	
	UFUNCTION(BlueprintImplementableEvent, Blueprintcallable)
	void SetDamageText(float Damage, bool bBlockedHit, bool bCriticalHit);
};
