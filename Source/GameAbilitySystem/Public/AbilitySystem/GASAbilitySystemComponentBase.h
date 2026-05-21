// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GASAbilitySystemComponentBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&);
/**
 * 
 */
UCLASS()
class GAMEABILITYSYSTEM_API UGASAbilitySystemComponentBase : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AbilityActorInfoSet();	
	
	FEffectAssetTags EffectAssetTags;//名为EffectAssetTags的多播代理，用于在效果应用时广播效果的标签容器
	
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	
	//AbilityInputTagHeld
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	//AbilityInputTagReleased
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
protected:
	
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle) const;

};
