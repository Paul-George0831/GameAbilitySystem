// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/AttributeMenuWidgetController.h"
#include "AbilitySystem/GASAttributeSetBase.h"
#include "Data/AttributeInfo.h"


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UGASAttributeSetBase* AS = Cast<UGASAttributeSetBase>(_AttributeSet);
	if (!AS || !_AbilitySystemComponent || !AttributeInfos)
	{
		return;
	}

	for (const auto& Pair : AS->TagToAttribute)
	{
		FGameplayAttribute Attribute = Pair.Value();
		_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda(
		[this, &Pair](const FOnAttributeChangeData& Data)
		{	
			BroadcastAuraAttributeInfo(Pair.Key, Pair.Value());
		}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UGASAttributeSetBase* AS = Cast<UGASAttributeSetBase>(_AttributeSet);
	
	for (const TPair<FGameplayTag, FGameplayAttribute(*)()>& it : AS->TagToAttribute)
	{
		BroadcastAuraAttributeInfo(it.Key, it.Value());
	}
}

void UAttributeMenuWidgetController::BroadcastAuraAttributeInfo(const FGameplayTag& Tag, const FGameplayAttribute& Attribute) const 
{
	FAuraAttributeInfo Info = AttributeInfos->FindAttributeByTag(Tag);//目的是拼合TagToAttribute + AttributeInfos的数据，找到当前标签在数据资产的额外信息
	Info.AttributeValue = Attribute.GetNumericValue(_AttributeSet);//属性值是动态数据
	AttributeInfoDelegate.Broadcast(Info);//每个Button都执行事件，避免了遍历每个Button组件
}
