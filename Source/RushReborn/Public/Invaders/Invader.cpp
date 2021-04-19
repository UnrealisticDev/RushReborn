#include "Invader.h"
#include "Combat/StatsComponent.h"
#include "Combat/Teams.h"

AInvader::AInvader()
	: bIsEngaged(false)
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Stats->HealthDepleted.AddDynamic(this, &AInvader::OnHealthDepleted);
}

uint8 AInvader::GetTeamId()
{
	return (uint8)ETeams::Invader;
}

bool AInvader::IsEngaged() const
{
	return bIsEngaged;
}

void AInvader::SetEngaged(bool bNewEngaged)
{
	bIsEngaged = bNewEngaged;
}

bool AInvader::IsAlive() const
{
	return Stats->CurrentHealth > 0.f;
}

void AInvader::OnHealthDepleted()
{
	Destroy();
}
