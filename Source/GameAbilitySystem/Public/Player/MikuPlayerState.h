// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "MikuPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class GAMEABILITYSYSTEM_API AMikuPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	AMikuPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	
protected:
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Level, Category = "Character Class Defaults")
	int32 Level = 1;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);
};
