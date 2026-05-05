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
	
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties(){};
	
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	
	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
};

UCLASS()
class GAMEABILITYSYSTEM_API UGASAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UGASAttributeSetBase();//auraattributeset
	
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Health)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, MaxHealth)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Mana)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, MaxMana)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Strength)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Intelligence)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Resilience)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Vigor)
	
	 UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category="Primary Attributes")
	 FGameplayAttributeData Strength;
	
	 UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category="Primary Attributes")
	 FGameplayAttributeData Intelligence;
	
	 UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category="Primary Attributes")
	 FGameplayAttributeData Resilience;
	
	 UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category="Primary Attributes")
	 FGameplayAttributeData Vigor;
	
	 UFUNCTION()
	 void OnRep_Strength(const FGameplayAttributeData& oldStrength) const;
	
	 UFUNCTION()
	 void OnRep_Intelligence(const FGameplayAttributeData& oldIntelligence) const;
	
	 UFUNCTION()
	 void OnRep_Resilience(const FGameplayAttributeData& oldResilience) const;
	
	 UFUNCTION()
	 void OnRep_Vigor(const FGameplayAttributeData& oldVigor) const;
	
	//重写一个函数注册网络复制，告诉引擎哪些类成员需要同步，用什么规则同步
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	//在实际值真正改变前调用
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	//当GE生效的时候调用
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	//创建一个健康值变量，给健康值绑定一个网络同步健康值的回调函数
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Vital Attribute")
	FGameplayAttributeData Health;
	//如果回调函数带参数，那么这个参数必须为服务器的旧值
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& oldHealth) const;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category="Vital Attribute")
	FGameplayAttributeData MaxHealth;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const;
	
	//魔力相关
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Vital Attribute")
	FGameplayAttributeData Mana;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Vital Attribute")
	FGameplayAttributeData MaxMana;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& oldMana) const;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& oldMaxMana) const;
	
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	
	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
private:
	
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
