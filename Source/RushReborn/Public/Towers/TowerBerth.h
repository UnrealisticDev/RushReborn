#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/SelectableInterface.h"
#include "TowerBerth.generated.h"

class UTowerActionMenuWidget;
class UWidgetComponent;
class UTowerAction;
class ATower;
class USphereComponent;
class UStaticMeshComponent;
class UDecalComponent;

/**
 * A TowerBerth is a station that can have
 * an arbitrary tower placed upon it.
 */
UCLASS(Blueprintable)
class ATowerBerth : public AActor, public ISelectableInterface
{
	GENERATED_BODY()

public:

	ATowerBerth();

	//~ Begin ISelectableInterface
	void OnSelected(ISelectorInterface* Selector) override;
	void OnUnselected(ISelectorInterface* Selector) override;
	//~ End ISelectableInterface

	/** Get the currently placed tower. */
	ATower* GetTower() const;

	/** Set the currently placed tower. */
	void SetTower(ATower* NewTower);

	/** Remove the currently placed tower. */
	void RemoveTower();

protected:

	/** Get a list of tower actions to display. */
	TArray<UTowerAction*> GetActions() const;

	/** Display tower actions. */
	void ShowActions(ISelectorInterface* Selector);

	/** Hide tower actions. */
	void HideActions();

	/** Get the tower action widget. */
	UTowerActionMenuWidget* GetActionMenuWidget() const;

	/** Show the range decal. */
	void ShowRangeIndicator();

	/** Hide the range decal. */
	void HideRangeIndicator();

	/** The currently placed tower. */
	UPROPERTY()
	ATower* Tower;

	/** A list of available tower actions when no tower has been placed. */
	UPROPERTY(EditAnywhere, Instanced, Category = Actions)
	TArray<UTowerAction*> Actions;

	/** The clickable area to interact with this berth. */
	UPROPERTY(VisibleAnywhere)
	USphereComponent* InteractionZone;

	/** The tower action menu component. */
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ActionMenu;

	/** Shows the range of a placed tower. */
	UPROPERTY(VisibleAnywhere)
	UDecalComponent* RangeIndicatorDecal;
};
