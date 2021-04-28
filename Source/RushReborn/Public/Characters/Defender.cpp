#include "Defender.h"
#include "Combat/DamageTypes.h"
#include "Combat/StatsComponent.h"
#include "Combat/StatsWidget.h"
#include "Combat/Teams.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

ADefender::ADefender()
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Stats->HealthDepleted.AddDynamic(this, &ADefender::OnHealthDepleted);

	Healthbar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Healthbar"));
	Healthbar->SetDrawSize(FVector2D(50, 5));
	Healthbar->SetWidgetSpace(EWidgetSpace::Screen);
	Healthbar->SetupAttachment(GetRootComponent());

	AttackDelay = 0.5f;
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
	return (uint8)ETeams::Defender;
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

IEngageeInterface* ADefender::GetEngagee() const
{
	return (IEngageeInterface*)Engaged.GetInterface();
}

bool ADefender::IsAlive() const
{
	return Stats->CurrentHealth > 0.f;
}

void ADefender::Attack(AActor* Target)
{
	PlayAnimMontage(AttackMontages[FMath::RandRange(0, AttackMontages.Num() - 1)]);

	FTimerHandle AttackTimer;
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, [this, Target]()
	{
		if (!this || !Target)
		{
			return;
		}
		
		const float DamageAmount = FMath::RandRange(Stats->AttackDamage.GetLowerBoundValue(), Stats->AttackDamage.GetUpperBoundValue());
		FDamageEvent DamageEvent;
		DamageEvent.DamageTypeClass = UPhysicalDamage::StaticClass();
		Target->TakeDamage(DamageAmount, DamageEvent, GetController(), this);
	},
		AttackDelay, false);
}

float ADefender::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	GetWorld()->GetTimerManager().SetTimer(RegenTimer, this, &ADefender::RegenHealth, 1.f, true, 2.f);

	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ADefender::RegenHealth()
{
	Stats->CurrentHealth = FMath::Clamp(Stats->CurrentHealth + 10, 0.f, Stats->MaxHealth);

	if (Stats->CurrentHealth == Stats->MaxHealth)
	{
		GetWorld()->GetTimerManager().ClearTimer(RegenTimer);
	}
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
