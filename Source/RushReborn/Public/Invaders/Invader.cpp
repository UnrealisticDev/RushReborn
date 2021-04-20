#include "Invader.h"
#include "AIController.h"
#include "SplineMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/DamageTypes.h"
#include "Combat/StatsComponent.h"
#include "Combat/StatsWidget.h"
#include "Combat/Teams.h"
#include "Components/WidgetComponent.h"
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

	IsEngagedKeyName = TEXT("bIsEngaged");
	ActorEngagedWithKeyName = TEXT("ActorEngagedWith");
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

bool AInvader::IsEngaged() const
{
	return ActorEngagedWith != nullptr;
}

AActor* AInvader::GetActorEngagedWith() const
{
	return ActorEngagedWith;
}

void AInvader::Engage(AActor* ActorToEngage)
{
	ActorEngagedWith = ActorToEngage;
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->GetBlackboardComponent()->SetValueAsBool(IsEngagedKeyName, true);
		AIController->GetBlackboardComponent()->SetValueAsObject(ActorEngagedWithKeyName, ActorToEngage);
	}
}

void AInvader::Disengage()
{
	ActorEngagedWith = nullptr;
	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		AIController->GetBlackboardComponent()->SetValueAsBool(IsEngagedKeyName, false);
		AIController->GetBlackboardComponent()->SetValueAsObject(ActorEngagedWithKeyName, nullptr);
	}
}

bool AInvader::IsAlive() const
{
	return Stats->CurrentHealth > 0.f;
}

void AInvader::Attack(AActor* Target)
{
	check(Target);

	float DamageAmount = FMath::RandRange(Stats->AttackDamage.GetLowerBoundValue(), Stats->AttackDamage.GetUpperBoundValue());
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
