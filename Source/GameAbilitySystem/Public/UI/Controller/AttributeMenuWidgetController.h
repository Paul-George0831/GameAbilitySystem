// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Controller/MikuWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FGameplayTag;
struct FGameplayAttribute;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAuraAttributeInfo&, Info);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class GAMEABILITYSYSTEM_API UAttributeMenuWidgetController : public UMikuWidgetController
{
	GENERATED_BODY()

public:
	
	virtual void BindCallbacksToDependencies() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues() override;
	
	UPROPERTY(BlueprintAssignable, Category = "AttributeInfo")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeInfo> AttributeInfos;

	void BroadcastAuraAttributeInfo(const FGameplayTag& Tag, const FGameplayAttribute& Attribute) const;
};
