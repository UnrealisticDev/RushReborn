#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "RushSpectatorPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * A barebones pawn that serves as the
 * camera target for the player.
 */
UCLASS()
class ARushSpectatorPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:

	ARushSpectatorPawn();

private:

	/** The spring arm that holds the camera. */
	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

	/** The main game camera. */
	UPROPERTY()
	UCameraComponent* CameraComponent;
};

