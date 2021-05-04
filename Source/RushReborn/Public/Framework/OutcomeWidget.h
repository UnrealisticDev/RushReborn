#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OutcomeWidget.generated.h"

UCLASS(Blueprintable)
class UOutcomeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Initialize the widget. */
	UFUNCTION(BlueprintImplementableEvent)
	void Init(bool bWon);	
};
