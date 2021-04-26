#pragma once

#include "CoreMinimal.h"
#include "Towers/TowerAction.h"
#include "TowerAction_Rally.generated.h"

/**
 * Initiates targeting for rallying
 * on towers that support rallying.
 */
UCLASS(Meta = (DisplayName = "Rally"))
class UTowerAction_Rally : public UTowerAction
{
	GENERATED_BODY()

public:

	UTowerAction_Rally();

	void Execute(const FTowerActionContext& Context) override;
};
