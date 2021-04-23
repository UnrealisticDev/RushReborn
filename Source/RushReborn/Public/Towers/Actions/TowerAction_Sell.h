#pragma once

#include "CoreMinimal.h"
#include "Towers/TowerAction.h"
#include "TowerAction_Sell.generated.h"

UCLASS(Meta=(DisplayName="Sell"))
class UTowerAction_Sell : public UTowerAction
{
	GENERATED_BODY()

public:

	UTowerAction_Sell();

	void Execute(const FTowerActionContext& Context);

protected:

	UPROPERTY(EditAnywhere, Category = Sell)
	int32 SetupValue;

	UPROPERTY(EditAnywhere, Category = Sell)
	int32 SpawningValue;
};
