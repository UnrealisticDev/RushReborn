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
	
	void Select();
	void Unselect();

protected:

	UPROPERTY(BlueprintReadOnly, Meta=(ExposeOnSpawn))
	UTowerAction* Action;

	UPROPERTY(BlueprintReadOnly, Meta=(ExposeOnSpawn))
	FTowerActionContext Context;
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

	UPROPERTY(EditAnywhere)
	float RadialOffset;

	UPROPERTY()
	UTowerAction* LastSelectedAction;
};
