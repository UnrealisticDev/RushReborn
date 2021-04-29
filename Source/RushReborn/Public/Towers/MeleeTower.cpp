#include "MeleeTower.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AI/DefenderState.h"

USoldierDeathTracker::USoldierDeathTracker()
{
	bWantsInitializeComponent = true;
}

void USoldierDeathTracker::InitializeComponent()
{
	Super::InitializeComponent();
}

void USoldierDeathTracker::UninitializeComponent()
{
	Died.ExecuteIfBound();
	
	Super::UninitializeComponent();
}

AMeleeTower::AMeleeTower()
	: InfluenceRadius(300.f)
	, RallyOffset(40.f)
{
	
}

void AMeleeTower::BeginPlay()
{
	Super::BeginPlay();

	SetStartingRallyPoint();

	for (int i = 0; i < 3; ++i)
	{
		SpawnSoldier(i);
	}
}

void AMeleeTower::SetStartingRallyPoint()
{
	while (true)
	{
		FVector RandomPoint(FMath::RandPointInCircle(InfluenceRadius), 0);
		RandomPoint += GetActorLocation();
		FHitResult TargetableTest;
		GetWorld()->LineTraceSingleByChannel
		(
			TargetableTest, 
			RandomPoint + FVector(0, 0, 100), 
			RandomPoint - FVector(0, 0, 100),
			ECollisionChannel::ECC_GameTraceChannel1 /* Targeting */
		);

		if (TargetableTest.IsValidBlockingHit())
		{
			RallyPoint = RandomPoint;
			break;
		}
	}
}

FVector AMeleeTower::CalculateHomeLocation(int32 Index)
{
	float Angle = 30.f + (120.f * Index);
	FVector HomeOffset
	(
		UKismetMathLibrary::DegSin(Angle) * RallyOffset,
		UKismetMathLibrary::DegCos(Angle) * RallyOffset,
		0.f
	);

	return RallyPoint + HomeOffset;
}

void AMeleeTower::SpawnSoldier(int32 Index)
{
	check(SoldierClass);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	APawn* Soldier = Cast<APawn>(GetWorld()->SpawnActorAbsolute(SoldierClass, GetActorTransform(), SpawnParams));
	if (!Soldier)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't open soldier."));
		return;
	}
	
	USoldierDeathTracker* DeathTracker = NewObject<USoldierDeathTracker>(Soldier);
	DeathTracker->Died.BindUObject(this, &AMeleeTower::OnSoldierDied, Index);
	DeathTracker->RegisterComponent();

	if (AAIController* AIController = Cast<AAIController>(Soldier->GetController()))
	{
		AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("Home"), CalculateHomeLocation(Index));
	}

	Soldiers[Index] = Soldier;
}

void AMeleeTower::OnSoldierDied(int32 Index)
{
	if (bManualDestroy)
	{
		return;
	}

	FTimerHandle ThrowawayHandle;
	FTimerDelegate RespawnDelegate;
	RespawnDelegate.BindUObject(this, &AMeleeTower::SpawnSoldier, Index);
	GetWorld()->GetTimerManager().SetTimer(ThrowawayHandle, RespawnDelegate, 10.f, false);
}

bool AMeleeTower::CanRally(FVector NewRallyPoint) const
{
	const bool bWithinRange = FVector::Dist(GetActorLocation(), NewRallyPoint) <= InfluenceRadius;

	FHitResult HitTargetingZone;
	GetWorld()->LineTraceSingleByChannel
	(
		HitTargetingZone, 
		NewRallyPoint + FVector(0, 0, 100.f), 
		NewRallyPoint + FVector(0, 0, -100.f),
		ECollisionChannel::ECC_GameTraceChannel1 /* Targeting */
	);

	const bool bInTargetingZone = HitTargetingZone.IsValidBlockingHit();

	return bWithinRange && bInTargetingZone;
}

void AMeleeTower::Rally(FVector NewRallyPoint)
{
	check(CanRally(NewRallyPoint));

	RallyPoint = NewRallyPoint;
	for (int Index = 0; Index < 3; ++Index)
	{
		const TWeakObjectPtr<APawn> Soldier = Soldiers[Index];
		if (AAIController* AIController = Cast<AAIController>(Soldier->GetController()))
		{
			AIController->GetBlackboardComponent()->SetValueAsVector(TEXT("Home"), CalculateHomeLocation(Index));
			AIController->GetBlackboardComponent()->SetValueAsEnum(TEXT("State"), (uint8)EDefenderState::Rally);
		}
	}
}

void AMeleeTower::Destroyed()
{
	bManualDestroy = true;

	for (const TWeakObjectPtr<APawn>& Soldier : Soldiers)
	{
		if (Soldier.IsValid())
		{
			Soldier->Destroy();
		}
	}

	Super::Destroyed();
}
