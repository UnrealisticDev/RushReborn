#pragma once

#include "CoreMinimal.h"
#include "Towers/TowerAction.h"
#include "TowerAction_Make.generated.h"

class ATower;

/**
 * Makes a new tower on the source
 * tower berth for the specified cost.
 */
UCLASS(Meta=(DisplayName="Make"))
class UTowerAction_Make : public UTowerAction
{
	GENERATED_BODY()

public:

	UTowerAction_Make();

	bool CanExecute(const FTowerActionContext& Context) override;
	void Execute(const FTowerActionContext& Context) override;

protected:

	/** The tower to make. */
	UPROPERTY(EditAnywhere, Category = Make)
	TSubclassOf<ATower> TowerClass;
};
