// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MikuPlayerState.h"
#include "AbilitySystem/GASAttributeSetBase.h"
#include "AbilitySystem/GASAbilitySystemComponentBase.h"

AMikuPlayerState::AMikuPlayerState()
{
	//设置服务器更新到客户端的频率
	NetUpdateFrequency = 100.f;

	//创建能力组件，并且让其参与网络复制
	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponentBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSetBase>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AMikuPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
