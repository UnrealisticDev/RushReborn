#include "ReinforcementCharacter.h"
#include "Combat/StatsComponent.h"
#include "Combat/Teams.h"

AReinforcementCharacter::AReinforcementCharacter()
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
}

uint8 AReinforcementCharacter::GetTeamId()
{
	return (uint8)ETeams::Player;
}
