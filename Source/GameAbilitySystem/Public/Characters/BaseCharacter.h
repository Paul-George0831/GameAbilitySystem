#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h" 
#include "BaseCharacter.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class AWeapon;
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class GAMEABILITYSYSTEM_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void BeginPlay() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual FVector GetCombatSocketLocation() const override;
	
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;	
	
	void AddCharacterAbilities() const;
	
	UPROPERTY(EditAnywhere, Category = "Character | Combat")
	FName WeaponTipSocketName;
	
	virtual void Die() override;
	
	UFUNCTION(NetMulticast, Reliable)
	/*
	 *NetMulticast — 服务器调用时，此函数会在服务器和所有连接的客户端上执行。只能从服务器调用，不能在客户端上调用。
	 *Reliable — 保证该 RPC 一定会到达所有连接的客户端，即使发生丢包也会重传，且保证按顺序处理。
	 * 
	 */
	
	virtual void MulticastHandleDeath();
	
	/*GE属性集*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Primary Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Secondary Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Vital Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttribute;
	/*End*/
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Items")
	TObjectPtr<UStaticMeshComponent> CurWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapon")
	TSubclassOf<AWeapon> DefaultWeaponClass;

	virtual void InitializeDefaultAttributes() const;
	
	/*ASC&&AS*/
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void InitAbilityActorInfo();
	/*End*/
	
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* HitReactMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartWeaponDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);
	
	void Dissolve();
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Primary Attributes")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
};
