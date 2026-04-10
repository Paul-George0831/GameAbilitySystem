#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GASAttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
	
UCLASS()
class GAMEABILITYSYSTEM_API UGASAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UGASAttributeSetBase();
	
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Health)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, MaxHealth)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Mana)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, MaxMana)
	
	//重写一个函数注册网络复制，告诉引擎哪些类成员需要同步，用什么规则同步
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	//创建一个健康值变量，给健康值绑定一个网络同步健康值的回调函数
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Vital Attribute")
	FGameplayAttributeData Health;
	//如果回调函数带参数，那么这个参数必须为服务器的旧值
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& oldHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category="Vital Attribute")
	FGameplayAttributeData MaxHealth;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth);
	
	//魔力相关
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Vital Attribute")
	FGameplayAttributeData Mana;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Vital Attribute")
	FGameplayAttributeData MaxMana;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& oldMana);
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& oldMaxMana);
	
};
