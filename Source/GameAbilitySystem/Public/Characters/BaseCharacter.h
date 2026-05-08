#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h" 
#include "BaseCharacter.generated.h"

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
protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Items")
	AWeapon* CurWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character | Weapon")
	TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void InitAbilityActorInfo();
};
