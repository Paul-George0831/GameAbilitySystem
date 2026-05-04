// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/OverlayWidgetController.h"

#include "AbilitySystem/GASAbilitySystemComponentBase.h"
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
	
	_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);//把获得的委托绑定到this的Healthchange函数
	_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		});
	_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		});
	_AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		});

	Cast<UGASAbilitySystemComponentBase>(_AbilitySystemComponent)->EffectAssetTags.AddLambda(//执行数据变化的逻辑都在controller层，所以在这里绑定委托EffectAssetTags
		[this](const FGameplayTagContainer& AssetTagContainer)->void
		{
			for (const FGameplayTag& AssetTag : AssetTagContainer)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (AssetTag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, AssetTag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}	
	);
}
