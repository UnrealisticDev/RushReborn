#pragma once

#include "CoreMinimal.h"
#include "TowerActionContext.generated.h"

class ATowerBerth;
class ATower;

USTRUCT()
struct FTowerActionContext
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TWeakObjectPtr<ATowerBerth> TowerBerth;
};
