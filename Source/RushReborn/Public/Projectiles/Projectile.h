#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

/**
 * The base class for all projectiles.
 * Provides common functionality like caching
 * start location, setting target, and impact
 * detection, but leaves movement and other
 * implementation details to subclasses.
 */
UCLASS(Blueprintable)
class AProjectile : public AActor
{
	GENERATED_BODY()

public:

	AProjectile();
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

private:
	
	/** Cache the start location. */
	void CacheStartLocation();

public:

	/** Set the target. */
	void SetTarget(AActor* InTarget);
	void SetTarget(FVector InTarget);

protected:

	/** Movement tick. */
	virtual void Move(float DeltaSeconds);

	/**
	 * Cache the target location, if it is an actor.
	 * Useful for continuing movement if target actor
	 * dies out from under us.
	 */
	void CacheTargetLocation();

	/** Returns true if target is within threshold distance. */
	bool HasReachedTarget() const;

	/** Called on impact. */
	virtual void Impact();

	/** Spawns impact particle, if specified. */
	void SpawnImpactParticle();

	/** Cached location where this projectile spawned. */
	UPROPERTY()
	FVector StartLocation;

	/** Target aimed at. */
	UPROPERTY()
	AActor* Target;

	/** Target location aimed at. */
	UPROPERTY()
	FVector TargetLocation;

	/** Distance to target to count as impact. */
	UPROPERTY()
	float TargetThreshold;

	/** Speed of travel. */
	UPROPERTY(EditAnywhere, Category = Movement)
	float FlightSpeed;

	/**
	 * Height of travel for projectiles that have
	 * parabolic movement.
	 */
	UPROPERTY(EditAnywhere, Category = Movement)
	float ArcHeight;

	/** Particle to spawn on impact. */
	UPROPERTY(EditAnywhere, Category = Impact)
	UParticleSystem* ImpactParticle;

	/** Scale to spawn impact particle at. */
	UPROPERTY(EditAnywhere, Category = Impact)
	FVector ImpactParticleScale;
};
