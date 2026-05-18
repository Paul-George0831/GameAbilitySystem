// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FAuraAttributeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttributeValue = 0.0f;
};	

UCLASS()
class GAMEABILITYSYSTEM_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FAuraAttributeInfo FindAttributeByTag(const FGameplayTag& AttributeTag, bool bLogNotFind = false) const;	

	//在蓝图初始化
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAuraAttributeInfo> AttributeInfos;
	
};
