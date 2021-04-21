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

UCLASS(Blueprintable)
class ATowerBerth : public AActor, public ISelectableInterface
{
	GENERATED_BODY()

public:

	ATowerBerth();

	void OnSelected(ISelectorInterface* Selector) override;
	void OnUnselected(ISelectorInterface* Selector) override;

	void SetTower(ATower* NewTower);
	void RemoveTower();

protected:

	TArray<UTowerAction*> GetActions() const;
	void ShowActions(ISelectorInterface* Selector);
	void HideActions();

	UTowerActionMenuWidget* GetActionMenuWidget() const;

	UPROPERTY()
	ATower* Tower;

	UPROPERTY(EditAnywhere, Instanced, Category = Actions)
	TArray<UTowerAction*> Actions;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* InteractionZone;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ActionMenu;
};
