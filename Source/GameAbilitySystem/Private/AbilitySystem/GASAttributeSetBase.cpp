#include "AbilitySystem/GASAttributeSetBase.h"
#include "Net/UnrealNetwork.h"

UGASAttributeSetBase::UGASAttributeSetBase()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitMana(50.f);
	InitMaxMana(50.f);
}

void UGASAttributeSetBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME_CONDITION_NOTIFY，UE的网络同步注册指令
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSetBase, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSetBase, MaxMana, COND_None, REPNOTIFY_Always);
}

void UGASAttributeSetBase::OnRep_Health(const FGameplayAttributeData& oldHealth)
{
	//通知ASC组件已经完成了网络同步Health，同时让能力系统（ASC）能够记录这个变化，以便服务器发现异常值回滚
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, Health, oldHealth);
}

void UGASAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, MaxHealth, oldMaxHealth);
}

void UGASAttributeSetBase::OnRep_Mana(const FGameplayAttributeData& oldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, Mana, oldMana);
}

void UGASAttributeSetBase::OnRep_MaxMana(const FGameplayAttributeData& oldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, MaxMana, oldMaxMana);
}
