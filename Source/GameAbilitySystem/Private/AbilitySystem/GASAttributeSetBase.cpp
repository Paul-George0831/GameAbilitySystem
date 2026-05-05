#include "AbilitySystem/GASAttributeSetBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UGASAttributeSetBase::UGASAttributeSetBase()
{
	/*ATTRIBUTE_ACCESSORS自动生成
	float GetHealth() const;
	void SetHealth(float Val);
	void InitHealth(float Val);
	*/
	InitHealth(60.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
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
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSetBase, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSetBase, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSetBase, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSetBase, Vigor, COND_None, REPNOTIFY_Always);
	
}

void UGASAttributeSetBase::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());//5.5之前这么写不行，但是5.5之后对newvalue钳值是可以修改修饰符的值的
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UGASAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	

}

void UGASAttributeSetBase::OnRep_Strength(const FGameplayAttributeData& oldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, Strength, oldStrength);
}

void UGASAttributeSetBase::OnRep_Intelligence(const FGameplayAttributeData& oldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, Intelligence, oldIntelligence);
}

void UGASAttributeSetBase::OnRep_Resilience(const FGameplayAttributeData& oldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, Resilience, oldResilience);
}

void UGASAttributeSetBase::OnRep_Vigor(const FGameplayAttributeData& oldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, Vigor, oldVigor);
}

void UGASAttributeSetBase::OnRep_Health(const FGameplayAttributeData& oldHealth) const
//需要使用UPROPERTY宏ReplicatedUsing = OnRep_Health来绑定回调
{
	//通知ASC组件已经完成了网络同步Health，同时让能力系统（ASC）能够记录这个变化，以便服务器发现异常值回滚
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, Health, oldHealth);
}

void UGASAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, MaxHealth, oldMaxHealth);
}

void UGASAttributeSetBase::OnRep_Mana(const FGameplayAttributeData& oldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, Mana, oldMana);
}

void UGASAttributeSetBase::OnRep_MaxMana(const FGameplayAttributeData& oldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSetBase, MaxMana, oldMaxMana);
}

void UGASAttributeSetBase::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.Get()->GetInstigatorAbilitySystemComponent();
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		//const AController* SourceController = SourceAvatarActor->GetInstigatorController();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* _Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = _Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			//_Pawn有可能为nullptr，并且作用域与这个if不同，所以只有当sourcecharacter强转成功才强转sourcecharacter
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	
	if (IsValid(&Data.Target) && IsValid(Data.Target.GetAvatarActor()))
	{
		Props.SourceAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.SourceCharacter = Cast<ACharacter>(Props.SourceCharacter);
		Props.SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.SourceAvatarActor);
	}
}
