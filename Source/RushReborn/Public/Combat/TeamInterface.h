#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TeamInterface.generated.h"

UINTERFACE(meta=(CannotImplementInterfaceInBlueprints))
class UTeamAgentInterface : public UInterface
{
	GENERATED_BODY()
};

class ITeamAgentInterface
{
	GENERATED_BODY()

public:

	virtual uint8 GetTeamId() { return -1; };
};
