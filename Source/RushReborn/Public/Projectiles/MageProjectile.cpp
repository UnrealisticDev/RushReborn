#include "MageProjectile.h"
#include "Combat/DamageTypes.h"
#include "Combat/StatsComponent.h"
#include "Kismet/GameplayStatics.h"

AMageProjectile::AMageProjectile()
{
	FlightSpeed = 800.f;
}

void AMageProjectile::Move(float DeltaSeconds)
{
	const FVector NewLocation = FMath::VInterpConstantTo
	(
		GetActorLocation(),
		TargetLocation,
		DeltaSeconds,
		FlightSpeed
	);

	SetActorLocation(NewLocation);
}

void AMageProjectile::Impact()
{
	ApplyDamageToTarget();
}

void AMageProjectile::ApplyDamageToTarget()
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
	DamageEvent.DamageTypeClass = UMagicalDamage::StaticClass();
	Target->TakeDamage(DamageAmount, DamageEvent, GetInstigatorController(), this);
}
