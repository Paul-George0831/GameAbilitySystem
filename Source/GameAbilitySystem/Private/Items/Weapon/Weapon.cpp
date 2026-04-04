// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon/Weapon.h"

AWeapon::AWeapon()
{
	ItemMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AWeapon::Equip(USceneComponent* InParent, FName SocketName, AActor* NewOwner, APawn* NewInstigator)
{
	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	FAttachmentTransformRules AttachTransInfo = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, AttachTransInfo, SocketName);

}
