#pragma once

#include "CoreMinimal.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Character.h"
#include "ReinforcementCharacter.generated.h"

class UStatsComponent;

UCLASS(Blueprintable)
class AReinforcementCharacter : public ACharacter, public ITeamAgentInterface
{
	GENERATED_BODY()

public:

	AReinforcementCharacter();
	
	uint8 GetTeamId() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStatsComponent* Stats;
};
