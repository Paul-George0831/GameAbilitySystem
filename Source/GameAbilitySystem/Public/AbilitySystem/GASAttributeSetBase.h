#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraGameplayTags.h"
#include "GASAttributeSetBase.generated.h"

//通常如果需要监听某个属性，就得使用GetAttribute()这个函数，而GetAttribute这个函数返回值就是FGameplayAttribute
//DECLARE_DELEGATE_RetVal(FGameplayAttribute, FGameplayAttributeSignature)

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FGameplayTag;

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
	
	// 定义一个别名，代表“返回 FGameplayAttribute 的无参函数指针”
	using FAttributeGetterPtr = FGameplayAttribute(*)();
	
	UGASAttributeSetBase();//auraattributeset
	
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Health)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Mana)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Strength)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Intelligence)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Resilience)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Vigor)
	
	//
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, MaxHealth)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, MaxMana)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, Armor)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, ArmorPenetration)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, BlockChance)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, CriticalHitChance)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, CriticalHitDamage)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, CriticalHitResilience)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, HealthRegeneration)
	ATTRIBUTE_ACCESSORS(UGASAttributeSetBase, ManaRegeneration)
	
	//不能使用UPROPERTY宏来存放值类型为自定义委托的TMap
	//函数指针内存开销以及调用开销更小，同时如果需要UPROPERTY序列化存储TMap也可以执行，而委托不支持序列化
	/*在不需要知道上下文，不需要蓝图绑定事件，不需要一对多广播，不需要序列化和网络同步的情况下，使用函数指针较好*/
	TMap<FGameplayTag, 	FAttributeGetterPtr> TagToAttribute;
	
	 UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category="Primary Attributes")
	 FGameplayAttributeData Strength;
	
	 UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category="Primary Attributes")
	 FGameplayAttributeData Intelligence;
	
	 UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category="Primary Attributes")
	 FGameplayAttributeData Resilience;
	
	 UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category="Primary Attributes")
	 FGameplayAttributeData Vigor;
	
	//
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category="Secondary Attributes")
	FGameplayAttributeData Armor;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category="Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category="Secondary Attributes")
	FGameplayAttributeData BlockChance;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResilience, Category="Secondary Attributes")
	FGameplayAttributeData CriticalHitResilience;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category="Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category="Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Secondary Attribute")
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category="Secondary Attribute")
	FGameplayAttributeData MaxHealth;
    //
	
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& oldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& oldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& oldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& oldVigor) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& oldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& oldArmorPenetration) const;

	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& oldBlockChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& oldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& oldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResilience(const FGameplayAttributeData& oldCriticalHitResilience) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& oldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& oldManaRegeneration) const;

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
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& oldMaxHealth) const;
	
	//魔力相关
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Vital Attribute")
	FGameplayAttributeData Mana;
	
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
