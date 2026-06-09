// Fill out your copyright notice in the Description page of Project Settings.


#include "BluepirntFunction/AuraBlueprintFunctionLibrary.h"

#include "AbilitySystemComponent.h"
#include "GameMode/GAS_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/MikuPlayerState.h"
#include "UI/Controller/MikuWidgetController.h"
#include "UI/HUD/MikuHUD.h"

UOverlayWidgetController* UAuraBlueprintFunctionLibrary::GetOverlayWidgetController(UObject* WorldContext)
{
	if (APlayerController* _PC = UGameplayStatics::GetPlayerController(WorldContext, 0))//通过世界上下文和玩家索引就能知道是哪个世界
	{
		if (AMikuHUD* _MHUD = _PC->GetHUD<AMikuHUD>())
		{
			//(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
			AMikuPlayerState* _PS = _PC->GetPlayerState<AMikuPlayerState>();
			UAbilitySystemComponent* ASC = _PS->GetAbilitySystemComponent();
			UAttributeSet* AS  = _PS->GetAttributeSet();
			const FMikuWidgetControllerParams _Params(_PC, _PS, ASC, AS);
			return _MHUD->GetOverlayWidgetController(_Params);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraBlueprintFunctionLibrary::GetAttributeMenuWidgetController(UObject* WorldContext)
{
	if (APlayerController* _PC = UGameplayStatics::GetPlayerController(WorldContext, 0))
	{
		if (AMikuHUD* _MHUD = _PC->GetHUD<AMikuHUD>())
		{
			//(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
			AMikuPlayerState* _PS = _PC->GetPlayerState<AMikuPlayerState>();
			UAbilitySystemComponent* ASC = _PS->GetAbilitySystemComponent();
			UAttributeSet* AS  = _PS->GetAttributeSet();
			const FMikuWidgetControllerParams _Params(_PC, _PS, ASC, AS);
			return _MHUD->GetAttributeMenuWidgetController(_Params);
		}
	}
	return nullptr;
}

void UAuraBlueprintFunctionLibrary::InitializeDefaultAttributes(const UObject* WorldContext,
	ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AGAS_GameModeBase* GameModeBase = Cast<AGAS_GameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if (!GameModeBase) return;
	
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = GameModeBase->CharacterClassInfo;
	const FCharacterClassDefaultInfo CharacterClassDefaultInfo = CharacterClassInfo->FindClassDefaultInfo(CharacterClass);
	FGameplayEffectContextHandle GameplayEffectContextHandle = ASC->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryGameplayEffectSpec = ASC->MakeOutgoingSpec(CharacterClassDefaultInfo.PrimaryAttributes, Level, GameplayEffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryGameplayEffectSpec.Data.Get());
	
	const FGameplayEffectSpecHandle SecondaryGameplayEffectSpec = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, GameplayEffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryGameplayEffectSpec.Data.Get());
	
	const FGameplayEffectSpecHandle VitalGameplayEffectSpec = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, GameplayEffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalGameplayEffectSpec.Data.Get());
}

void UAuraBlueprintFunctionLibrary::GiveStartupAbilities(const UObject* WorldContext, UAbilitySystemComponent* ASC)
{
	AGAS_GameModeBase* GameModeBase = Cast<AGAS_GameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if (!GameModeBase) return;
	
	for (const auto AbilityClass : GameModeBase->CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec GAspec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(GAspec);
	}
}
