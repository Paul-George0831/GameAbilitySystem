// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GASAbilitySystemComponentBase.h"

#include "AbilitySystem/Abilities/AuraGameplayAbility.h"


void UGASAbilitySystemComponentBase::AbilityActorInfoSet()
{
	//当GE应用到自身，这一行的作用就是绑定EffectApplied到OnGameplayEffectAppliedDelegateToSelf事件
	//OnGameplayEffectAppliedDelegateToSelf只在服务器端完成回调
	//ClientEffectApplied是一个RPC，把客户端的函数绑定到服务器委托上
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UGASAbilitySystemComponentBase::ClientEffectApplied);
}

void UGASAbilitySystemComponentBase::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const auto& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec(AbilityClass, 1);
		if (const UAuraGameplayAbility* AuraAbility = Cast<UAuraGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.GetDynamicSpecSourceTags().AddTag(AuraAbility->StartupInputTag);
			GiveAbility(AbilitySpec);//Grants an Ability,Returns handle that can be used in TryActivateAbility
		}
	}
}

void UGASAbilitySystemComponentBase::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())//防止重复激活Ability
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UGASAbilitySystemComponentBase::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UGASAbilitySystemComponentBase::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle) const
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
