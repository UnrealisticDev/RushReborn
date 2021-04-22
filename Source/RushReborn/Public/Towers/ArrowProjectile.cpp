#include "ArrowProjectile.h"
#include "Combat/DamageTypes.h"
#include "Combat/StatsComponent.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"

AArrowProjectile::AArrowProjectile()
	: MoveAlpha(0.f)
{
	
}

void AArrowProjectile::Move(float DeltaSeconds)
{
	MoveAlpha = FMath::Clamp(MoveAlpha + DeltaSeconds, 0.f, 1.f);

	const FVector ArcVertex = CalculateArcVertex();
	const FVector LerpStartToVertex = FMath::Lerp(StartLocation, ArcVertex, MoveAlpha);
	const FVector LerpVertexToTarget = FMath::Lerp(ArcVertex, TargetLocation, MoveAlpha);

	const FVector OldLocation = GetActorLocation();
	const FVector NewLocation = FMath::Lerp(LerpStartToVertex, LerpVertexToTarget, MoveAlpha);
	SetActorLocation(NewLocation);

	const FVector NewRotation = NewLocation - OldLocation;
	SetActorRotation(NewRotation.Rotation());
}

void AArrowProjectile::Impact()
{
	ApplyDamageToTarget();
}

FVector AArrowProjectile::CalculateArcVertex() const
{
	FVector Midpoint = (GetActorLocation() + TargetLocation) / 2;	
	return Midpoint + FVector(0, 0, ArcHeight);
}

void AArrowProjectile::ApplyDamageToTarget()
{
	if (!Target)
	{
		return;
	}
	
	float DamageAmount = 0.f;
	if (UStatsComponent* InstigatorStats = GetInstigator()->FindComponentByClass<UStatsComponent>())
	{
		const FFloatRange& DamageRange = InstigatorStats->AttackDamage;
		DamageAmount = FMath::RandRange(DamageRange.GetLowerBoundValue(), DamageRange.GetUpperBoundValue());
	}
	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = UPhysicalDamage::StaticClass();
	Target->TakeDamage(DamageAmount, DamageEvent, GetInstigatorController(), this);
}
