#pragma once

#include "CoreMinimal.h"
#include "Towers/TowerAction.h"
#include "TowerAction_Sell.generated.h"

/**
 * Sells the source tower for the amount specified,
 * depending on which phase the game is currently in.
 */
UCLASS(Config=Game, HideCategories=(Display, Cost), Meta=(DisplayName="Sell"))
class UTowerAction_Sell : public UTowerAction
{
	GENERATED_BODY()

public:

	UTowerAction_Sell();

	FText GetDescription() const override;
	void Execute(const FTowerActionContext& Context) override;

protected:

	/** Gold earned if sold during Setup phase. */
	UPROPERTY(EditAnywhere, Category = Sell)
	int32 SetupValue;

	/** Gold earned if sold during Spawning phase. */
	UPROPERTY(EditAnywhere, Category = Sell)
	int32 SpawningValue;

private:

	/** Sound to play on execute. */
	UPROPERTY(Config)
	FSoftObjectPath ExecuteSound;
};
