#pragma once

#include "CoreMinimal.h"
#include "Towers/TowerAction.h"
#include "TowerAction_Make.generated.h"

class ATower;
class ADecalActor;
class UMaterialInterface;

/**
 * Makes a new tower on the source
 * tower berth for the specified cost.
 */
UCLASS(Config=Game, Meta=(DisplayName="Make"))
class UTowerAction_Make : public UTowerAction
{
	GENERATED_BODY()

public:

	UTowerAction_Make();

	void Select(const FTowerActionContext& Context) override;
	void Unselect(const FTowerActionContext& Context) override;
	
	bool CanExecute(const FTowerActionContext& Context) override;
	void Execute(const FTowerActionContext& Context) override;

protected:

	/** The tower to make. */
	UPROPERTY(EditAnywhere, Category = Make)
	TSubclassOf<ATower> TowerClass;

	/** Range indicator. */
	UPROPERTY();
	ADecalActor* RangeIndicator;

	/** Range indicator material. */
	UPROPERTY(Config)
	FSoftObjectPath RangeIndicatorMaterial;

private:

	/** Sound to play on execute. */
	UPROPERTY(Config)
	FSoftObjectPath ExecuteSound;
};
