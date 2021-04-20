#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/SelectableInterface.h"
#include "TowerBerth.generated.h"

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

protected:

	UPROPERTY()
	ATower* Tower;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* InteractionZone;
};
