#include "RangedTower.h"
#include "Components/SphereComponent.h"
#include "Combat/StatsComponent.h"
#include "Projectiles/Projectile.h"

ARangedTower::ARangedTower()
{
	InfluenceBounds = CreateDefaultSubobject<USphereComponent>(TEXT("InfluenceBounds"));
	SetRootComponent(InfluenceBounds);
	
	Stats = CreateDefaultSubobject<UStatsComponent>(TEXT("Stats"));

	AttackDelay = 0.5f;
}

void ARangedTower::Attack(AActor* Target)
{
	check(ProjectileClass);

	OnAttack(Target);

	FTimerHandle AttackTimer;
	GetWorld()->GetTimerManager().SetTimer
	(
		AttackTimer,
		[this, Target]()
		{
			if (!this || !Target)
			{
				return;
			}
			
			FActorSpawnParameters SpawnParams;
			SpawnParams.Instigator = this;
			AProjectile* Projectile = Cast<AProjectile>(
				GetWorld()->SpawnActorAbsolute(ProjectileClass, GetSpawnPoint(), SpawnParams));
			Projectile->SetTarget(Target);
		},
		AttackDelay, false);
}
