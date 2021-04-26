#pragma once

#include "CoreMinimal.h"
#include "TowerActionContext.generated.h"

class ISelectorInterface;
class ATowerBerth;
class ATower;

/**
 * Generic context for tower actions.
 * This provides relevant state while
 * allowing actions to be generally
 * source-agnostic.
 */
USTRUCT(BlueprintType)
struct FTowerActionContext
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TWeakObjectPtr<ATowerBerth> TowerBerth;

	UPROPERTY()
	TScriptInterface<ISelectorInterface> Selector;
};
