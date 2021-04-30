#include "Tower.h"
#include "Combat/Teams.h"

uint8 ATower::GetTeamId()
{
	return (uint8)ETeams::Defender;
}

float ATower::GetInfluenceRadius() const
{
	return 1.f;
}

