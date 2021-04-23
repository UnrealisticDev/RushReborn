#include "RangedTower.h"
#include "Components/SphereComponent.h"
#include "Combat/StatsComponent.h"
#include "Projectiles/Projectile.h"

ARangedTower::ARangedTower()
{
	InfluenceBounds = CreateDefaultSubobject<USphereComponent>(TEXT("InfluenceBounds"));
	SetRootComponent(InfluenceBounds);
	
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));
}

void ARangedTower::Attack(AActor* Target)
{
	check(ProjectileClass);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	AProjectile* Projectile = Cast<AProjectile>(GetWorld()->SpawnActorAbsolute(ProjectileClass, GetSpawnPoint(), SpawnParams));
	Projectile->SetTarget(Target);
	
	OnAttack(Target);
}
