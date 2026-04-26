// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/OverlayWidgetController.h"

#include "AbilitySystem/GASAttributeSetBase.h"

void UOverlayWidgetController::BroadcastInitialValues()//如果只绑定变化委托，UI 刚创建时没有任何事情会告诉它当前属性是多少，界面可能会显示 0 或未定义的状态，需要在初始阶段广播值
{
	const UGASAttributeSetBase* _AS = CastChecked<UGASAttributeSetBase>(_AttributeSet);
	
	OnHealthChanged.Broadcast(_AS->GetHealth());
	OnMaxHealthChanged.Broadcast(_AS->GetMaxHealth());
	OnManaChanged.Broadcast(_AS->GetMana());
	OnMaxManaChanged.Broadcast(_AS->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UGASAttributeSetBase* _AS = CastChecked<UGASAttributeSetBase>(_AttributeSet);
	
	_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);	
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);	
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
