// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/OverlayWidgetController.h"

#include "AbilitySystem/GASAttributeSetBase.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UGASAttributeSetBase* _AS = CastChecked<UGASAttributeSetBase>(_AttributeSet);
	
	OnHealthChanged.Broadcast(_AS->GetHealth());
	OnMaxHealthChanged.Broadcast(_AS->GetMaxHealth());

}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UGASAttributeSetBase* _AS = CastChecked<UGASAttributeSetBase>(_AttributeSet);
	
	_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);	
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);	
}
