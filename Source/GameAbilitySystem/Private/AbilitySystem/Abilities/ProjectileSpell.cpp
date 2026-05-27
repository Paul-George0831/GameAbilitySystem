// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ProjectileSpell.h"

#include "Actors/AuraProjectile.h"
#include "Interfaces/CombatInterface.h"

void UProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsOnServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsOnServer) return;
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	FTransform SpawnTransform;
	if(CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		const FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
	}
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Projectile->FinishSpawning(SpawnTransform);
}

void UProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo,
                                       const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}
