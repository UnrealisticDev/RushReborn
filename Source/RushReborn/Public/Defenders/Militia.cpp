#include "Militia.h"
#include "Combat/DamageTypes.h"
#include "Combat/StatsComponent.h"
#include "Combat/Teams.h"
#include "GameFramework/CharacterMovementComponent.h"

AMilitia::AMilitia()
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Stats->MaxHealth = Stats->CurrentHealth = 50;
	Stats->Armor = 0;
	Stats->MagicResistance = 0;
	Stats->AttackDamage = FFloatRange(1, 3);
	Stats->AttackRate = 1.f;

	Stats->HealthDepleted.AddDynamic(this, &AMilitia::OnHealthDepleted);
}

void AMilitia::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = Stats->MovementSpeed;
}

uint8 AMilitia::GetTeamId()
{
	return (uint8)ETeams::Player;
}

bool AMilitia::IsEngaged() const
{
	return ActorEngagedWith != nullptr;
}

AActor* AMilitia::GetActorEngagedWith() const
{
	return ActorEngagedWith;
}

void AMilitia::Engage(AActor* ActorToEngage)
{
	ActorEngagedWith = ActorToEngage;
	if (ICombatantInterface* EngagedCombatant = Cast<ICombatantInterface>(ActorToEngage))
	{
		EngagedCombatant->Engage(this);
	}
}

void AMilitia::Disengage()
{
	if (ICombatantInterface* EngagedCombatant = Cast<ICombatantInterface>(ActorEngagedWith))
	{
		EngagedCombatant->Disengage();
	}
	ActorEngagedWith = nullptr;
}

bool AMilitia::IsAlive() const
{
	return Stats->CurrentHealth > 0.f;
}

void AMilitia::Attack(AActor* Target)
{
	const float AttackDamage = FMath::RandRange(Stats->AttackDamage.GetLowerBoundValue(), Stats->AttackDamage.GetUpperBoundValue());
	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = UPhysicalDamage::StaticClass();
	Target->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
}

void AMilitia::OnHealthDepleted()
{
	Destroy();
}

void AMilitia::Destroyed()
{
	Disengage(); // Don't hang on to any enemies that we might be engaged with
	
	Super::Destroyed();
}
