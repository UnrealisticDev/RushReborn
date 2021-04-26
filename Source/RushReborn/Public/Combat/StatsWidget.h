#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatsWidget.generated.h"

class UStatsComponent;

/**
 * A Stats widget is a barebones
 * base class to be used by widgets that
 * want to showcase information from a
 * source Stats component.
 *
 * The source component has to be set manually.
 */
UCLASS(Blueprintable)
class UStatsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetSource(UStatsComponent* InSource);

private:
	
	UPROPERTY(BlueprintReadOnly, Meta=(AllowPrivateAccess="true"))
	UStatsComponent* Source;
};
