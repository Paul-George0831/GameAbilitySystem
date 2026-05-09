// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/GASAttributeSetBase.h"
#include "Interfaces/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UGASAttributeSetBase::GetVigorAttribute();//只告知需要捕获哪个属性，与具体的对象无关
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;//设为 Target，表示从 GE 的目标对象身上取值
	VigorDef.bSnapshot = false;
	
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//FGameplayEffectSpec 在运行时包含了对 Source 和 Target 对象的具体引用,只要 AttributeSource == Target，系统就会获取到带有GE被施加者身上找 Vigor 的数值；设为 Source 就去GE施加者身上找Vigor，从而计算
	const FGameplayTagContainer* SourceTagContainer = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTagContainer = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTagContainer;
	EvaluateParameters.TargetTags = TargetTagContainer;
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);
	ICombatInterface* __CBI = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = __CBI->GetPlayerLevel();
	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
