#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RallyCoordinatorInterface.generated.h"

/**
 * Exposes functionality for rallying
 * at a given point.
 */
UINTERFACE(Meta=(CannotImplementInterfaceInBlueprints))
class URallyCoordinatorInterface : public UInterface
{
	GENERATED_BODY()
};

class IRallyCoordinatorInterface
{
	GENERATED_BODY()

public:

	/** Returns true if the coordinator can rally at the given point. */
	virtual bool CanRally(FVector NewRallyPoint) const = 0;

	/** Rally at the given point. */
	virtual void Rally(FVector NewRallyPoint) = 0;
};
