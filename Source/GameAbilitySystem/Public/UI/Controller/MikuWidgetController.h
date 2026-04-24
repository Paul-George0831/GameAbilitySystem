// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MikuWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FMikuWidgetControllerParams
{
	GENERATED_BODY()
	
	FMikuWidgetControllerParams(){};
	FMikuWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: _PlayerController(PC), _PlayerState(PS), _AbilitySystemComponent(ASC), _AttributeSet(AS) {}
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<APlayerController> _PlayerController = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<APlayerState> _PlayerState = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UAbilitySystemComponent> _AbilitySystemComponent = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UAttributeSet> _AttributeSet = nullptr;
};

UCLASS()
class GAMEABILITYSYSTEM_API UMikuWidgetController : public UObject
{
	GENERATED_BODY()
	
public:
	//设置控制器，玩家状态，ASC组件，属性集等组件
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FMikuWidgetControllerParams& params);
	
	virtual void BroadcastInitialValues();
	
	virtual void BindCallbacksToDependencies();
	
protected:
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> _PlayerController;//当一个游戏有多个角色，且玩家可以随意更换，通过获取到玩家控制器从而访问到玩家角色的属性是最好的方法
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> _PlayerState;//通过玩家状态获取属性集和ASC
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> _AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> _AttributeSet;
};
