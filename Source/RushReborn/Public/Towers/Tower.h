#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tower.generated.h"

class UTowerAction;

UCLASS()
class ATower : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Instanced, Category = Actions)
	TArray<UTowerAction*> Actions;
};
