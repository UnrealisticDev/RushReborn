#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "RainOfFireAbility.generated.h"

UCLASS(Config=Game)
class URainOfFireAbility : public UAbility
{
	GENERATED_BODY()

public:

	URainOfFireAbility();

	void Activate(const FAbilityPayload& Payload) override;

private:

	void SpawnProjectile();

	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY(Config)
	FSoftClassPath ProjectileClass;

	UPROPERTY()
	int32 ProjectileCount;

	UPROPERTY()
	int32 ProjectilesSpawned;

	UPROPERTY()
	float ProjectileSpawnRadius;

	UPROPERTY()
	float ProjectileSpawnHeight;

	UPROPERTY()
	float ProjectileSpawnInterval;

	UPROPERTY()
	FTimerHandle ProjectileSpawnTimer;
};
