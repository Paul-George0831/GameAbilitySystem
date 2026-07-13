#pragma once
#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsBlockHit() const { return bIsBlockHit; }
	bool IsCriticalHit() const { return bIsCriticalHit; }
	
	void SetIsBlockHit(bool InIsBlockHit) { bIsBlockHit = InIsBlockHit; }
	void SetIsCriticalHit(bool InIsCriticalHit) { bIsCriticalHit = InIsCriticalHit; }
	
	virtual UScriptStruct* GetStruct() const
	{
		return StaticStruct();
	}
	
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;
	
	virtual FAuraGameplayEffectContext* Duplicate() const
	{
		FAuraGameplayEffectContext* NewContext = new FAuraGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
	
protected:

	UPROPERTY()
	bool bIsBlockHit = false;
	
	UPROPERTY()
	bool bIsCriticalHit = false;

};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};