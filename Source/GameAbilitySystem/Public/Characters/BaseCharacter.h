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

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;	
	
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
	AWeapon* CurWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapon")
	TSubclassOf<AWeapon> DefaultWeaponClass;

	/*ASC&&AS*/
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void InitAbilityActorInfo();
	/*End*/
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Primary Attributes")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
};
