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
	bool IsAbilitySelected(TSubclassOf<UAbility> AbilityClass) const;
	void SelectAbility(TSubclassOf<UAbility> AbilityClass);
	void UnselectAbility();

private:

	UPROPERTY()
	UAbility* Reinforcements;

	UPROPERTY()
	UAbility* RainOfFire;

	enum class EAbilitySelected : uint8
	{
		None,
		Reinforcements,
		RainofFire
	};

	EAbilitySelected SelectedAbility;
};
