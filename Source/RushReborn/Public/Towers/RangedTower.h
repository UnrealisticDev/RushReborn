#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatantInterface.h"
#include "Towers/Tower.h"
#include "RangedTower.generated.h"

class UStatsComponent;
class USphereComponent;
class AProjectile;

/**
 * The RangedTower is the base class
 * for archer, mage, and bombard towers.
 */
UCLASS()
class ARangedTower : public ATower, public ICombatantInterface
{
	GENERATED_BODY()

public:

	ARangedTower();

	//~ Begin ICombatantInterface
	void Attack(AActor* Target) override;
	//~ End ICombatantInterface

	/** Get the transform to spawn projectiles at. */
	UFUNCTION(BlueprintImplementableEvent)
	FTransform GetSpawnPoint() const;

	/** Callback for when this tower attacks. */
	UFUNCTION(BlueprintImplementableEvent)
	void OnAttack(AActor* Target);

protected:

	/** The area within which this tower can attack. */
	UPROPERTY(VisibleAnywhere)
	USphereComponent* InfluenceBounds;

	/** Stats component. */
	UPROPERTY(VisibleAnywhere)
	UStatsComponent* Stats;

	/** The projectile to spawn. */
	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AProjectile> ProjectileClass;

	/** Delay in spawning projectile. */
	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackDelay;
};
