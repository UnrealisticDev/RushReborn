#include "BombardProjectile.h"
#include "Combat/DamageTypes.h"
#include "Combat/StatsComponent.h"
#include "Combat/TeamUtilities.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"

ABombardProjectile::ABombardProjectile()
	: MoveAlpha(0.f)
	, AreaOfEffect(200.f)
{
	
}

void ABombardProjectile::Move(float DeltaSeconds)
{
	MoveAlpha = FMath::Clamp(MoveAlpha + DeltaSeconds, 0.f, 1.f);

	const FVector ArcVertex = CalculateArcVertex();
	const FVector LerpStartToVertex = FMath::Lerp(StartLocation, ArcVertex, MoveAlpha);
	const FVector LerpVertexToTarget = FMath::Lerp(ArcVertex, TargetLocation, MoveAlpha);

	const FVector OldLocation = GetActorLocation();
	const FVector NewLocation = FMath::Lerp(LerpStartToVertex, LerpVertexToTarget, MoveAlpha);
	SetActorLocation(NewLocation);
}

void ABombardProjectile::Impact()
{
	ApplyDamageInArea();
}

FVector ABombardProjectile::CalculateArcVertex() const
{
	FVector Midpoint = (GetActorLocation() + TargetLocation) / 2;	
	return Midpoint + FVector(0, 0, ArcHeight);
}

void ABombardProjectile::ApplyDamageInArea()
{
	float DamageAmount = 0.f;
	if (UStatsComponent* InstigatorStats = GetInstigator()->FindComponentByClass<UStatsComponent>())
	{
		const FFloatRange& DamageRange = InstigatorStats->AttackDamage;
		DamageAmount = FMath::RandRange(DamageRange.GetLowerBoundValue(), DamageRange.GetUpperBoundValue());
	}
	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = UPhysicalDamage::StaticClass();

	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByChannel
	(
		Hits, 
		GetActorLocation(), 
		GetActorLocation() + 1, 
		FQuat::Identity, 
		ECollisionChannel::ECC_Pawn, 
		FCollisionShape::MakeSphere(AreaOfEffect)
	);

	for (const FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (UTeamUtilities::AreEnemies(GetInstigator(), HitActor))
		{
			HitActor->TakeDamage(DamageAmount, DamageEvent, GetInstigatorController(), this);	
		}
	}
}
