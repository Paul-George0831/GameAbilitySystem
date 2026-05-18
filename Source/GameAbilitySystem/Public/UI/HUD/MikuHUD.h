// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MikuHUD.generated.h"

class UAttributeMenuWidgetController;
class UAttributeSet;
class UOverlayWidgetController;
class UAbilitySystemComponent;
class APlayerController;
class APlayerState;
class UMikuUserWidget;
struct FMikuWidgetControllerParams;
/**
 * 
 */
UCLASS()
class GAMEABILITYSYSTEM_API AMikuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	
	UOverlayWidgetController* GetOverlayWidgetController(const FMikuWidgetControllerParams& params);
	
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FMikuWidgetControllerParams& params);
	
	//接收四个变量，从而初始化overlayWidget实例
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,UAttributeSet* AS);
	
protected:
	
	
	
private:
	
	UPROPERTY()
	TObjectPtr<UMikuUserWidget> OverlayUserWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMikuUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributesMenuWidgetControllerClass;
};
