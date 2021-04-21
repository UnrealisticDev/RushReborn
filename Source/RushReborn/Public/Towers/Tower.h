#pragma once

#include "CoreMinimal.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Pawn.h"
#include "Tower.generated.h"

class UTowerAction;

UCLASS()
class ATower : public APawn, public ITeamAgentInterface
{
	GENERATED_BODY()

public:

	uint8 GetTeamId() override;

	UPROPERTY(EditAnywhere, Instanced, Category = Actions)
	TArray<UTowerAction*> Actions;
};
