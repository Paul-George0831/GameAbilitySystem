// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GASAbilitySystemComponentBase.h"


void UGASAbilitySystemComponentBase::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UGASAbilitySystemComponentBase::EffectApplied);//当GE应用到自身，这一行的作用就是绑定EffectApplied到OnGameplayEffectAppliedDelegateToSelf事件
}

void UGASAbilitySystemComponentBase::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle) const
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
