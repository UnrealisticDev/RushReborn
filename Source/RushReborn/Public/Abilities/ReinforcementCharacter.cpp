#include "ReinforcementCharacter.h"
#include "Combat/StatsComponent.h"
#include "Combat/Teams.h"
#include "GameFramework/CharacterMovementComponent.h"

AReinforcementCharacter::AReinforcementCharacter()
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Stats->MaxHealth = Stats->CurrentHealth = 30;
	Stats->Armor = 0;
	Stats->MagicResistance = 0;
	Stats->AttackDamage = FFloatRange(1, 2);
	Stats->AttackRate = 1.f;
}

void AReinforcementCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = Stats->MovementSpeed;
}

uint8 AReinforcementCharacter::GetTeamId()
{
	return (uint8)ETeams::Player;
}
