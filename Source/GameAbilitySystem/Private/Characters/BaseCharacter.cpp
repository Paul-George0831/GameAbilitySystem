#include "Characters/BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/GASAbilitySystemComponentBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	CurWeapon = CreateDefaultSubobject<UStaticMeshComponent>("Weapon");
	CurWeapon->SetupAttachment(GetMesh(), "WeaponHandSocket");
	CurWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FVector ABaseCharacter::GetCombatSocketLocation() const
{
	return CurWeapon->GetSocketLocation(WeaponTipSocketName);
}

void ABaseCharacter::InitAbilityActorInfo()
{
}

void ABaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(GetAbilitySystemComponent());
	check(GameplayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level,EffectContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ABaseCharacter::AddCharacterAbilities() const
{
	if (!HasAuthority()) return;
	UGASAbilitySystemComponentBase* _ASC = Cast<UGASAbilitySystemComponentBase>(AbilitySystemComponent);
	_ASC->AddCharacterAbilities(StartupAbilities);
}
