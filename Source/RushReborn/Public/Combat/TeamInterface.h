#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TeamInterface.generated.h"

/** Allows an actor to pick a team. */
UINTERFACE(meta=(CannotImplementInterfaceInBlueprints))
class UTeamAgentInterface : public UInterface
{
	GENERATED_BODY()
};

class ITeamAgentInterface
{
	GENERATED_BODY()

public:

	/** Get the agent's team id. */
	virtual uint8 GetTeamId() { return -1; };
};
