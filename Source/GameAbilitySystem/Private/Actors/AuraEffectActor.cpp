// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/AuraEffectActor.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "AbilitySystem/GASAttributeSetBase.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(StaticMesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());	
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}

void AAuraEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAuraEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCIterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		//获取类型为UGASAttributeSetBase的实例，由于getattributeset只能返回UAttributeSet所以这里只能设为UAttributeSet
		const UGASAttributeSetBase* MikuAttributeSet = Cast<UGASAttributeSetBase>(ASCIterface->GetAbilitySystemComponent()->GetAttributeSet(UGASAttributeSetBase::StaticClass()));
		UGASAttributeSetBase* MikuMutableAttributeSet = const_cast<UGASAttributeSetBase*>(MikuAttributeSet);
		MikuMutableAttributeSet->SetHealth(MikuAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

