// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/MikuWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
//分别给HP和MaxHP创建一个动态多播委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMP);

UCLASS(BlueprintType, Blueprintable)
class GAMEABILITYSYSTEM_API UOverlayWidgetController : public UMikuWidgetController
{
	GENERATED_BODY()
	
public:
	
	virtual void BroadcastInitialValues() override;
	
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;
protected:
	void HealthChanged(const FOnAttributeChangeData& Data) const;//当HP变化时的回调函数，注意函数签名要一致

	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;

	void ManaChanged(const FOnAttributeChangeData& Data) const;
	
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
