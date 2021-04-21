#pragma once

#include "CoreMinimal.h"
#include "TowerAction.h"
#include "TowerAction_Make.generated.h"

class ATower;

UCLASS(Meta=(DisplayName="Make"))
class UTowerAction_Make : public UTowerAction
{
	GENERATED_BODY()

public:

	UTowerAction_Make();

	UPROPERTY(EditAnywhere, Category = Make)
	TSubclassOf<ATower> TowerClass;
};
