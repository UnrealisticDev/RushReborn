#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatantInterface.generated.h"

class AActor;

/**
 * Exposes functionality for attacking a target
 * and checking the liveliness of the owner.
 */
UINTERFACE(meta = (CannotImplementInterfaceInBlueprints))
class UCombatantInterface : public UInterface
{
	GENERATED_BODY()
};

class ICombatantInterface
{
	GENERATED_BODY()

public:

	/** Returns true if the owner is alive. */
	virtual bool IsAlive() const { return true; }

	/** Attack the specified target. */
	virtual void Attack(AActor* Target) {}
};