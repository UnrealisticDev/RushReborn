#include "Projectile.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
	: TargetThreshold(10.f)
	, FlightSpeed(400.f)
	, ArcHeight(100.f)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CacheStartLocation();
}

void AProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CacheTargetLocation();
	Move(DeltaSeconds);
	if (HasReachedTarget())
	{
		Impact();
		SpawnImpactParticle();
		Destroy();
	}
}

void AProjectile::CacheStartLocation()
{
	StartLocation = GetActorLocation();
}

void AProjectile::SetTarget(AActor* InTarget)
{
	Target = InTarget;
	if (Target)
	{
		TargetLocation = Target->GetActorLocation();
	}
}

void AProjectile::SetTarget(FVector InTarget)
{
	TargetLocation = InTarget;
}

void AProjectile::Move(float DeltaSeconds)
{
	// no op
}

void AProjectile::CacheTargetLocation()
{
	if (Target)
	{
		TargetLocation = Target->GetActorLocation();
	}
}

bool AProjectile::HasReachedTarget() const
{
	return FVector::Dist(GetActorLocation(), TargetLocation) < TargetThreshold;
}

void AProjectile::Impact()
{
	// no op
}

void AProjectile::SpawnImpactParticle()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticle, GetActorLocation());
}
