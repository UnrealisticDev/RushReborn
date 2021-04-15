#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "RushSpectatorPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ARushSpectatorPawn : public ASpectatorPawn
{
	GENERATED_BODY()

public:

	ARushSpectatorPawn();

private:

	UPROPERTY()
	USpringArmComponent* SpringArmComponent;

	UPROPERTY()
	UCameraComponent* CameraComponent;
};

