#include "Invader.h"
#include "Combat/StatsComponent.h"
#include "Combat/StatsWidget.h"
#include "Combat/Teams.h"
#include "Components/WidgetComponent.h"

AInvader::AInvader()
	: bIsEngaged(false)
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Stats->HealthDepleted.AddDynamic(this, &AInvader::OnHealthDepleted);

	Healthbar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Healthbar"));
	Healthbar->SetDrawSize(FVector2D(100, 10));
	Healthbar->SetWidgetSpace(EWidgetSpace::Screen);
	Healthbar->SetupAttachment(GetRootComponent());
}

void AInvader::BeginPlay()
{
	Super::BeginPlay();

	if (UStatsWidget* StatsHealthbar = Cast<UStatsWidget>(Healthbar->GetWidget()))
	{
		StatsHealthbar->SetSource(Stats);
	}
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
