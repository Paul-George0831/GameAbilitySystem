#include "Characters/Enemy.h"
#include "AbilitySystem/GASAttributeSetBase.h"
#include "AbilitySystem/GASAbilitySystemComponentBase.h"

AEnemy::AEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//创建ASC插件以及属性集,设置其为可复制
	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponentBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UGASAttributeSetBase>(TEXT("AttributeSet"));
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void AEnemy::Highlight()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AEnemy::UnHighlight()
{
	GetMesh()->SetRenderCustomDepth(false);
}

int32 AEnemy::GetPlayerLevel() const
{
	return this->Level;
}

void AEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UGASAbilitySystemComponentBase>(AbilitySystemComponent)->AbilityActorInfoSet();
}
