#pragma once

#include "CoreMinimal.h"
#include "Abilities/Ability.h"
#include "ReinforcementsAbility.generated.h"

/**
 * The Reinforcements ability spawns
 * two defenders of the specified class
 * at the target location.
 */
UCLASS(Config=Game)
class UReinforcementsAbility : public UAbility
{
	GENERATED_BODY()

public:

	UReinforcementsAbility();

	bool CanActivate(const FAbilityPayload& Payload) override;
	void Activate(const FAbilityPayload& Payload) override;

private:

	/** The reinforcement class to spawn. */
	UPROPERTY(Config)
	FSoftClassPath SpawnClass;

	/**
	 * The offset from target location to spawn.
	 * (So that spawns are staggered radially)
	 */
	UPROPERTY()
	FVector SpawnOffset;
};
