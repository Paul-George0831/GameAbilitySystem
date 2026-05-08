// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MikuPlayerState.h"
#include "AbilitySystem/GASAttributeSetBase.h"
#include "AbilitySystem/GASAbilitySystemComponentBase.h"
#include "Net/UnrealNetwork.h"

AMikuPlayerState::AMikuPlayerState()
{
	//设置网络同步频率
	NetUpdateFrequency = 100.f;

	//创建ASC组件以及属性集
	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponentBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSetBase>(TEXT("AttributeSet"));
}

void AMikuPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMikuPlayerState, Level);
	 
	//DOREPLIFETIME_CONDITION_NOTIFY(AMikuPlayerState, Level, COND_None, REPNOTIFY_Always);
}

void AMikuPlayerState::OnRep_Level(int32 OldLevel)
{
}

UAbilitySystemComponent* AMikuPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
