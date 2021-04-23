#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RallyCoordinatorInterface.generated.h"

UINTERFACE(Meta=(CannotImplementInterfaceInBlueprints))
class URallyCoordinatorInterface : public UInterface
{
	GENERATED_BODY()
};

class IRallyCoordinatorInterface
{
	GENERATED_BODY()

public:

	virtual bool CanRally(FVector NewRallyPoint) const = 0;
	virtual void Rally(FVector NewRallyPoint) = 0;
};
