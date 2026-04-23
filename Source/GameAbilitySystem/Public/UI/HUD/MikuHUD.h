// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MikuHUD.generated.h"

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
	
	UPROPERTY()
	TObjectPtr<UMikuUserWidget> OverlayUserWidget;
	
	UOverlayWidgetController* GetOverlayWidgetController(const FMikuWidgetControllerParams& params);
	
	//接收四个变量，从而初始化overlayWidget实例
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC,UAttributeSet* AS);
	
protected:
	
	
	
private:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMikuUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
