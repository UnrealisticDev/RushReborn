#include "Invader.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "SplineMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/DamageTypes.h"
#include "Combat/StatsComponent.h"
#include "Combat/StatsWidget.h"
#include "Combat/Teams.h"
#include "Components/WidgetComponent.h"
#include "Framework/TowerDefenseEssentialsInterface.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

AInvader::AInvader(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USplineMovementComponent>(CharacterMovementComponentName))
{
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
	Stats->HealthDepleted.AddDynamic(this, &AInvader::OnHealthDepleted);

	Healthbar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Healthbar"));
	Healthbar->SetDrawSize(FVector2D(50, 5));
	Healthbar->SetWidgetSpace(EWidgetSpace::Screen);
	Healthbar->SetupAttachment(GetRootComponent());

	AttackDelay = 0.5f;
	
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

TArray<IEngagorInterface*> AInvader::GetEngagors() const
{
	TArray<IEngagorInterface*> Out;
	for (const TScriptInterface<IEngagorInterface>& Engagor : Engagors)
	{
		Out.Add((IEngagorInterface*)Engagor.GetInterface());
	}
	return Out;
}

bool AInvader::IsAlive() const
{
	return Stats->CurrentHealth > 0.f;
}

void AInvader::Attack(AActor* Target)
{
	check(Target);

	PlayAnimMontage(AttackMontages[FMath::RandRange(0, AttackMontages.Num() - 1)]);

	FTimerHandle AttackTimer;
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, [this, Target]()
	{
		if (!this || !Target)
		{
			return;
		}
		
		const float DamageAmount = FMath::RandRange(Stats->AttackDamage.GetLowerBoundValue(), Stats->AttackDamage.GetUpperBoundValue());
		FDamageEvent DamageEvent;
		DamageEvent.DamageTypeClass = UPhysicalDamage::StaticClass();
		Target->TakeDamage(DamageAmount, DamageEvent, GetController(), this);
	},
		AttackDelay, false);
}

void AInvader::OnHealthDepleted()
{
	if (!bDead)
	{
		bDead = true;
		Die();
	}
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

void AInvader::Die()
{
	if (ITowerDefenseEssentialsInterface* EssentialsGameMode = Cast<ITowerDefenseEssentialsInterface>(GetWorld()->GetAuthGameMode()))
	{
		EssentialsGameMode->AddGold(Bounty);	
	}

	if (IsPawnControlled())
	{
		Cast<AAIController>(GetController())->GetBrainComponent()->StopLogic("Death");
	}

	Healthbar->DestroyComponent();
	SetActorEnableCollision(false);
	GetMesh()->PlayAnimation(DeathAnimation, false);
	SetLifeSpan(2.f);

	UGameplayStatics::PlaySound2D(this, DeathSound, 0.5f);
}

void AInvader::Destroyed()
{
	Super::Destroyed();
}
