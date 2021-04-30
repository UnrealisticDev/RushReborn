#pragma once

#include "CoreMinimal.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Pawn.h"
#include "Tower.generated.h"

class UTowerAction;

/**
 * The base Tower class simply provides
 * team functionality and a list of
 * tower actions.
 */
UCLASS()
class ATower : public APawn, public ITeamAgentInterface
{
	GENERATED_BODY()

public:

	//~ Begin ITeamAgentInterface
	uint8 GetTeamId() override;
	//~ End ITeamAgentInterface

	/** The actions corresponding to this tower. */
	UPROPERTY(EditAnywhere, Instanced, Category = Actions)
	TArray<UTowerAction*> Actions;

	/** Get the range of this tower. */
	virtual float GetInfluenceRadius() const;
};
