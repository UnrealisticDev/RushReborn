#pragma once

#include "CoreMinimal.h"
#include "TowerActionContext.h"
#include "Blueprint/UserWidget.h"
#include "TowerActionWidgets.generated.h"

class UCanvasPanelSlot;
class UTowerAction;

/** A widget representing a single tower action. */
UCLASS()
class UTowerActionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Get the source tower action. */
	UFUNCTION(BlueprintPure)
	UTowerAction* GetAction() const;

	/** Returns true if the action can be executed. */
	UFUNCTION(BlueprintPure)
	bool CanBeExecuted() const;

	/** Select the action. */
	UFUNCTION(BlueprintCallable)
	void Select();

	/** Unselect the action. */
	void Unselect();

	DECLARE_DELEGATE_OneParam(FTowerActionCallback, UTowerActionWidget*);

	/** Selection/execution events. */
	FTowerActionCallback ActionSelected;
	FTowerActionCallback ActionExecuted;

protected:

	/** The source tower action. */
	UPROPERTY(BlueprintReadOnly, Meta=(ExposeOnSpawn))
	UTowerAction* Action;

	/** Context to be used by the action. */
	UPROPERTY(BlueprintReadOnly, Meta=(ExposeOnSpawn))
	FTowerActionContext Context;

	/** Flag set when waiting on action confirmation. */
	UPROPERTY(BlueprintReadOnly)
	bool bAwaitingConfirmation;
};

/** A widget to display a list of tower actions. */
UCLASS()
class UTowerActionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Show all actions. */
	UFUNCTION(BlueprintImplementableEvent)
	void Show(const TArray<UTowerAction*>& ActionsToShow, const FTowerActionContext& Context);

	/** Position action on menu. */
	UFUNCTION(BlueprintCallable)
	void PositionAction(UTowerActionWidget* ActionWidget, UCanvasPanelSlot* ActionSlot);

	/** Observe select/execute events from action. */
	UFUNCTION(BlueprintCallable)
	void SetupActionObservers(UTowerActionWidget* ActionWidget);

	/** Hide all actions. */
	UFUNCTION(BlueprintNativeEvent)
	void Hide();

protected:

	/** Informs other actions that they have been unselected. */
	void OnActionSelected(UTowerActionWidget* SelectedActionWidget);

	/** Closes menu. */
	void OnActionExecuted(UTowerActionWidget* ExecutedActionWidget);

	/** Distance from center to place actions. */
	UPROPERTY(EditAnywhere)
	float RadialOffset;
};
