#pragma once

#include "CoreMinimal.h"
#include "Teams.generated.h"

/** The full set of possible teams. */
UENUM()
enum class ETeams : uint8
{
	Defender,
	Invader
};