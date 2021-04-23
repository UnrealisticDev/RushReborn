#pragma once

#include "CoreMinimal.h"
#include "Towers/TowerAction.h"
#include "TowerAction_Make.generated.h"

class ATower;

UCLASS(Meta=(DisplayName="Make"))
class UTowerAction_Make : public UTowerAction
{
	GENERATED_BODY()

public:

	UTowerAction_Make();

	bool CanExecute(const FTowerActionContext& Context) override;
	void Execute(const FTowerActionContext& Context) override;

protected:

	UPROPERTY(EditAnywhere, Category = Make)
	TSubclassOf<ATower> TowerClass;
};
