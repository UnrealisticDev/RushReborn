#include "Invader.h"
#include "AIController.h"
#include "SplineMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/DamageTypes.h"
#include "Combat/StatsComponent.h"
#include "Combat/StatsWidget.h"
#include "Combat/Teams.h"
#include "Components/WidgetComponent.h"
#include "Framework/TowerDefenseEssentialsInterface.h"
#include "Math/UnrealMathUtility.h"

AInvader::AInvader(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USplineMovementComponent>(CharacterMovementComponentName))
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Stats->HealthDepleted.AddDynamic(this, &AInvader::OnHealthDepleted);

	Healthbar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Healthbar"));
	Healthbar->SetDrawSize(FVector2D(100, 10));
	Healthbar->SetWidgetSpace(EWidgetSpace::Screen);
	Healthbar->SetupAttachment(GetRootComponent());

	Bounty = -1;

	IsEngagedKeyName = TEXT("bIsEngaged");
	TargetKeyName = TEXT("Target");
}

void AInvader::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = Stats->MovementSpeed;
	if (UStatsWidget* StatsHealthbar = Cast<UStatsWidget>(Healthbar->GetWidget()))
	{
		StatsHealthbar->SetSource(Stats);
	}
}

uint8 AInvader::GetTeamId()
{
	return (uint8)ETeams::Invader;
}

void AInvader::EngagedBy(IEngagorInterface* Engagor)
{
	if (Engagor)
	{
		Engagors.Add(Cast<UObject>(Engagor));
		if (Engagors.Num() == 1)
		{
			if (AAIController* AIController = Cast<AAIController>(GetController()))
			{
				AIController->GetBlackboardComponent()->SetValueAsBool(IsEngagedKeyName, true);
				AIController->GetBlackboardComponent()->SetValueAsObject(TargetKeyName, Cast<UObject>(Engagor));
			}
		}
	}
}

void AInvader::DisengagedBy(IEngagorInterface* Engagor)
{
	if (Engagor)
	{
		Engagors.Remove(Cast<UObject>(Engagor));
		if (Engagors.Num() == 0)
		{
			if (AAIController* AIController = Cast<AAIController>(GetController()))
			{
				AIController->GetBlackboardComponent()->SetValueAsBool(IsEngagedKeyName, false);
			}
		}
	}
}

bool AInvader::IsEngaged() const
{
	return Engagors.Num() > 0;
}

int32 AInvader::GetEngagementCount() const
{
	return Engagors.Num();
}

bool AInvader::IsAlive() const
{
	return Stats->CurrentHealth > 0.f;
}

void AInvader::Attack(AActor* Target)
{
	check(Target);

	const float DamageAmount = FMath::RandRange(Stats->AttackDamage.GetLowerBoundValue(), Stats->AttackDamage.GetUpperBoundValue());
	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = UPhysicalDamage::StaticClass();
	Target->TakeDamage(DamageAmount, DamageEvent, GetController(), this);
}

void AInvader::OnHealthDepleted()
{
	Destroy();
}

void AInvader::SetSplineToFollow(USplineComponent* Spline)
{
	Cast<ISplineFollowInterface>(GetMovementComponent())->SetSplineToFollow(Spline);
}

void AInvader::StartSplineMovement()
{
	Cast<ISplineFollowInterface>(GetMovementComponent())->StartSplineMovement();
}

void AInvader::StopSplineMovement()
{
	Cast<ISplineFollowInterface>(GetMovementComponent())->StopSplineMovement();
}

float AInvader::GetRemainingDistanceAlongSpline()
{
	return Cast<ISplineFollowInterface>(GetMovementComponent())->GetRemainingDistanceAlongSpline();
}

void AInvader::Destroyed()
{
	Cast<ITowerDefenseEssentialsInterface>(GetWorld()->GetAuthGameMode())->AddGold(Bounty);
	
	Super::Destroyed();
}
