// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/HighlightInterface.h"
#include "Characters/BaseCharacter.h"
#include "Data/CharacterClassInfo.h"
#include "UI/Controller/OverlayWidgetController.h"
#include "Enemy.generated.h"

class UWidgetComponent;

UCLASS()
class GAMEABILITYSYSTEM_API AEnemy : public ABaseCharacter, public IHighlightInterface
{
	GENERATED_BODY()
	
public:

	AEnemy();

	virtual void BeginPlay() override;

	virtual void Highlight() override;
	virtual void UnHighlight() override;
	
	virtual int32 GetPlayerLevel() const override;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	virtual void Die() override;
	
protected:
	virtual  void InitAbilityActorInfo() override;
	
	UPROPERTY(BlueprintReadOnly)
	bool bHitReacting = false;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Character Class Defaults")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass Career = ECharacterClass::None;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
	
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;
	
private:
	
	float BaseWalkSpeed = 250.f;
	
};
