#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
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
protected:
	UPROPERTY(VisibleAnywhere, Category = "Vision")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Vision")
	UCameraComponent* Camera;

	void InitAbilityActorInfo();
};
