// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/HighlightInterface.h"
#include "Characters/BaseCharacter.h"
#include "Enemy.generated.h"

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
	
protected:
	virtual  void InitAbilityActorInfo() override;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Character Class Defaults")
	int32 Level = 1;
};
