#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RushPlayerController.generated.h"

class UAbility;

UCLASS()
class ARushPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void SetupInputComponent() override;
	void TestAbility();

	UPROPERTY()
	UAbility* Reinforcements;

	UPROPERTY()
	UAbility* RainOfFire;
};
