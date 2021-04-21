#pragma once

#include "CoreMinimal.h"
#include "TowerActionContext.h"
#include "Blueprint/UserWidget.h"
#include "TowerActionWidgets.generated.h"

class UCanvasPanelSlot;
class UTowerAction;

UCLASS()
class UTowerActionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	UTowerAction* GetAction() const;

	UFUNCTION(BlueprintPure)
	bool CanBeExecuted() const;

	UFUNCTION(BlueprintCallable)
	void Select();
	void Unselect();

	DECLARE_DELEGATE_OneParam(FTowerActionCallback, UTowerActionWidget*);

	FTowerActionCallback ActionSelected;
	FTowerActionCallback ActionExecuted;

protected:

	UPROPERTY(BlueprintReadOnly, Meta=(ExposeOnSpawn))
	UTowerAction* Action;

	UPROPERTY(BlueprintReadOnly, Meta=(ExposeOnSpawn))
	FTowerActionContext Context;

	UPROPERTY(BlueprintReadOnly)
	bool bAwaitingConfirmation;
};

UCLASS()
class UTowerActionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent)
	void Show(const TArray<UTowerAction*>& ActionsToShow, const FTowerActionContext& Context);

	UFUNCTION(BlueprintCallable)
	void PositionAction(UTowerActionWidget* ActionWidget, UCanvasPanelSlot* ActionSlot);
	
	UFUNCTION(BlueprintCallable)
	void SetupActionObservers(UTowerActionWidget* ActionWidget);

	UFUNCTION(BlueprintNativeEvent)
	void Hide();

protected:

	void OnActionSelected(UTowerActionWidget* SelectedActionWidget);
	void OnActionExecuted(UTowerActionWidget* ExecutedActionWidget);

	UPROPERTY(EditAnywhere)
	float RadialOffset;

	UPROPERTY()
	UTowerAction* LastSelectedAction;
};
