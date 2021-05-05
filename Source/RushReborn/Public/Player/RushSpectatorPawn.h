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
class ARushSpectatorPawn : public APawn
{
	GENERATED_BODY()

public:

	ARushSpectatorPawn();
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:

	/** Movement facilities. */
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	
	/** Zoom facilities. */
	void ZoomIn();
	void ZoomOut();
	void Zoom(float Delta);

	/** Root scene component. */
	UPROPERTY()
	USceneComponent* Root;
	
	/** The spring arm that holds the camera. */
	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

	/** The main game camera. */
	UPROPERTY()
	UCameraComponent* CameraComponent;
};

