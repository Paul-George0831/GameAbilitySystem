#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UGameplayEffect;
class UCameraComponent;
class AWeapon;

UCLASS()
class GAMEABILITYSYSTEM_API APlayerCharacter : public ABaseCharacter                
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();
	
	virtual void PossessedBy(AController* NewController) override;

	//当初始化成功playerstate的时候回调
	virtual void OnRep_PlayerState() override;
	
	void InitializeDefaultAttributes() const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Primary Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Secondary Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttribute;

	virtual int32 GetPlayerLevel() const override;
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Vision")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Vision")
	UCameraComponent* Camera;

	virtual void InitAbilityActorInfo() override;
};
