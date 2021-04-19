#include "ReinforcementCharacter.h"
#include "Combat/StatsComponent.h"
#include "Combat/Teams.h"

AReinforcementCharacter::AReinforcementCharacter()
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Stats->MaxHealth = Stats->CurrentHealth = 30;
	Stats->Armor = 0;
	Stats->MagicResistance = 0;
	Stats->AttackDamage = FFloatRange(1, 2);
	Stats->AttackRate = 1.f;
}

uint8 AReinforcementCharacter::GetTeamId()
{
	return (uint8)ETeams::Player;
}
