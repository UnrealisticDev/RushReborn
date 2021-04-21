#pragma once

#include "CoreMinimal.h"
#include "TowerActionContext.generated.h"

class ATowerBerth;
class ATower;

USTRUCT(BlueprintType)
struct FTowerActionContext
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TWeakObjectPtr<ATowerBerth> TowerBerth;
};
