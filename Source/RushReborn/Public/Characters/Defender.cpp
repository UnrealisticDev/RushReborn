#include "Defender.h"
#include "Combat/DamageTypes.h"
#include "Combat/StatsComponent.h"
#include "Combat/StatsWidget.h"
#include "Combat/Teams.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ADefender::ADefender()
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Stats->HealthDepleted.AddDynamic(this, &ADefender::OnHealthDepleted);

	Healthbar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Healthbar"));
	Healthbar->SetDrawSize(FVector2D(100, 10));
	Healthbar->SetWidgetSpace(EWidgetSpace::Screen);
	Healthbar->SetupAttachment(GetRootComponent());
}

void ADefender::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = Stats->MovementSpeed;
	if (UStatsWidget* StatsHealthbar = Cast<UStatsWidget>(Healthbar->GetWidget()))
	{
		StatsHealthbar->SetSource(Stats);
	}
}

uint8 ADefender::GetTeamId()
{
	return (uint8)ETeams::Player;
}

void ADefender::Engage(IEngageeInterface* Engagee)
{
	if (Engagee)
	{
		Engaged = Cast<UObject>(Engagee);
		Engaged->EngagedBy(this);
	}
}

void ADefender::Disengage()
{
	if (Engaged)
	{
		Engaged->DisengagedBy(this);
	}
	Engaged = nullptr;
}

bool ADefender::IsAlive() const
{
	return Stats->CurrentHealth > 0.f;
}

void ADefender::Attack(AActor* Target)
{
	const float AttackDamage = FMath::RandRange(Stats->AttackDamage.GetLowerBoundValue(), Stats->AttackDamage.GetUpperBoundValue());
	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = UPhysicalDamage::StaticClass();
	Target->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
}

void ADefender::OnHealthDepleted()
{
	Destroy();
}

void ADefender::Destroyed()
{
	Disengage(); // Don't hang on to any enemies that we might be engaged with
	
	Super::Destroyed();
}
