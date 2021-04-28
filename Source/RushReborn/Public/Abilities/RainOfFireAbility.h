#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "RainOfFireAbility.generated.h"

/**
 * The Rain of Fire ability spawns three projectiles above a
 * target location. Those projectiles crash down and cause
 * area of effect damage.
 */
UCLASS()
class URainOfFireAbility : public UAbility
{
	GENERATED_BODY()

public:

	URainOfFireAbility();

	bool CanActivate(const FAbilityPayload& Payload) override;
	void Activate(const FAbilityPayload& Payload) override;

private:

	/** Spawn a projectile above the target location. */
	void SpawnProjectile();

	/**
	 * The cached target location.
	 * Obtained from payload.
	 */
	UPROPERTY()
	FVector TargetLocation;

	/** The projectile to spawn. */
	UPROPERTY()
	UClass* ProjectileClass;

	/** The number of projectiles to spawn. */
	UPROPERTY()
	int32 ProjectileCount;

	/** The number of projectiles already spawned. */
	UPROPERTY()
	int32 ProjectilesSpawned;

	/** The radius in which to spawn projectiles. */
	UPROPERTY()
	float ProjectileSpawnRadius;

	/**
	 * The height above target location to
	 * spawn projectiles.
	 */
	UPROPERTY()
	float ProjectileSpawnHeight;

	/** The rate at which to spawn projectiles. */
	UPROPERTY()
	float ProjectileSpawnInterval;

	/** Timer for tracking projectile spawns. */
	UPROPERTY()
	FTimerHandle ProjectileSpawnTimer;
};
