 // Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AuraProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameAbilitySystem/GameAbilitySystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

 AAuraProjectile::AAuraProjectile()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

 	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
 	SetRootComponent(Sphere);
 	Sphere->SetCollisionObjectType(ECC_Projectile);
 	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
 	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
 	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
 	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
 	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

 	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
 	ProjectileMovement->InitialSpeed = 550.f;
 	ProjectileMovement->MaxSpeed = 550.f;
 	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();

 	SetLifeSpan(LifeSpan);

 	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereBeginOverlap);
 	Sphere->IgnoreActorWhenMoving(GetInstigator(), true);

 	if (LoopingSound)
 	{
 		LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
 	}
}

 void AAuraProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
		if (LoopingSoundComponent)
		{
			LoopingSoundComponent->Stop();
		}
	}
	Super::Destroyed();
}

 void AAuraProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
 {
 	if (OtherActor == GetInstigator() || bHit)
 		return;

 	bHit = true;

	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
 	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
 	if (LoopingSoundComponent)
 	{
 		LoopingSoundComponent->Stop();
 	}
 	if (HasAuthority())
 	{
 		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
 		{
 			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
 		}
 		Destroy();
 	}
 }
