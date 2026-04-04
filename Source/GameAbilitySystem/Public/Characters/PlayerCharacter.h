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

protected:
	UPROPERTY(VisibleAnywhere, Category = "Vision")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Vision")
	UCameraComponent* Camera;

};
