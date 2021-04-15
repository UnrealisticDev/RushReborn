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

	ARushPlayerController();
	void SetupInputComponent() override;
	void TestAbility();

	const UAbility* GetAbility(TSubclassOf<UAbility> AbilityClass);
	void OnAbilitySelected(TSubclassOf<UAbility> AbilityClass);
	void OnAbilityUnselected(TSubclassOf<UAbility> AbilityClass);

private:

	UPROPERTY()
	UAbility* Reinforcements;

	UPROPERTY()
	UAbility* RainOfFire;
};
