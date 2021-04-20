#include "ReinforcementCharacter.h"
#include "Combat/DamageTypes.h"
#include "Combat/StatsComponent.h"
#include "Combat/Teams.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"

AReinforcementCharacter::AReinforcementCharacter()
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Stats->MaxHealth = Stats->CurrentHealth = 30;
	Stats->Armor = 0;
	Stats->MagicResistance = 0;
	Stats->AttackDamage = FFloatRange(1, 2);
	Stats->AttackRate = 1.f;

	Stats->HealthDepleted.AddDynamic(this, &AReinforcementCharacter::OnHealthDepleted);
}

void AReinforcementCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = Stats->MovementSpeed;
	SetLifeSpan(20.f);
}

uint8 AReinforcementCharacter::GetTeamId()
{
	return (uint8)ETeams::Player;
}

bool AReinforcementCharacter::IsEngaged() const
{
	return ActorEngagedWith != nullptr;
}

AActor* AReinforcementCharacter::GetActorEngagedWith() const
{
	return ActorEngagedWith;
}

void AReinforcementCharacter::Engage(AActor* ActorToEngage)
{
	ActorEngagedWith = ActorToEngage;
	if (ICombatantInterface* EngagedCombatant = Cast<ICombatantInterface>(ActorToEngage))
	{
		EngagedCombatant->Engage(this);
	}
}

void AReinforcementCharacter::Disengage()
{
	if (ICombatantInterface* EngagedCombatant = Cast<ICombatantInterface>(ActorEngagedWith))
	{
		EngagedCombatant->Disengage();
	}
	ActorEngagedWith = nullptr;
}

bool AReinforcementCharacter::IsAlive() const
{
	return Stats->CurrentHealth > 0.f;
}

void AReinforcementCharacter::Attack(AActor* Target)
{
	const float AttackDamage = FMath::RandRange(Stats->AttackDamage.GetLowerBoundValue(), Stats->AttackDamage.GetUpperBoundValue());
	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = UPhysicalDamage::StaticClass();
	Target->TakeDamage(AttackDamage, DamageEvent, GetController(), this);
}

void AReinforcementCharacter::OnHealthDepleted()
{
	Destroy();
}
