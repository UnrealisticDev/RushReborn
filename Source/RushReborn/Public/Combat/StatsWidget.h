#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatsWidget.generated.h"

class UStatsComponent;

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
