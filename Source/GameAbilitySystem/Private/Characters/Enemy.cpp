#include "Characters/Enemy.h"
#include "AbilitySystem/GASAttributeSetBase.h"
#include "AbilitySystem/GASAbilitySystemComponentBase.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/MikuUserWidget.h"

AEnemy::AEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//创建ASC插件以及属性集,设置其为可复制
	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponentBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
	
	AttributeSet = CreateDefaultSubobject<UGASAttributeSetBase>(TEXT("AttributeSet"));
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
	UGASAttributeSetBase* _AS = Cast<UGASAttributeSetBase>(AttributeSet);
	if (UMikuUserWidget* EnemyUserWidget = Cast<UMikuUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		EnemyUserWidget->SetWidgetController(this);
	}
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)->void
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}	
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(_AS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)->void
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}	
	);
	
	OnHealthChanged.Broadcast(_AS->GetHealth());
	OnMaxHealthChanged.Broadcast(_AS->GetMaxHealth());
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
	
	InitializeDefaultAttributes();
}
