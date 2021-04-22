#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatantInterface.h"
#include "Towers/Tower.h"
#include "RangedTower.generated.h"

class UStatsComponent;
class USphereComponent;
class AProjectile;

UCLASS()
class ARangedTower : public ATower, public ICombatantInterface
{
	GENERATED_BODY()

public:

	ARangedTower();

	void Attack(AActor* Target) override;

	UFUNCTION(BlueprintImplementableEvent)
	FTransform GetSpawnPoint() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnAttack(AActor* Target);

protected:
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* InfluenceBounds;

	UPROPERTY(VisibleAnywhere)
	UStatsComponent* Stats;

	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AProjectile> ProjectileClass;
};
