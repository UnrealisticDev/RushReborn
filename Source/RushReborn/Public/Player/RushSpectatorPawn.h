#pragma once

#include "CoreMinimal.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/SpectatorPawn.h"
#include "RushSpectatorPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ARushSpectatorPawn : public ASpectatorPawn, public ITeamAgentInterface
{
	GENERATED_BODY()

public:

	ARushSpectatorPawn();

	uint8 GetTeamId() override;

private:

	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

	UPROPERTY()
	UCameraComponent* CameraComponent;
};

