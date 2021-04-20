#pragma once

#include "CoreMinimal.h"
#include "SelectorInterface.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/PlayerController.h"
#include "RushPlayerController.generated.h"

class ISelectableInterface;
class UAbility;

UCLASS()
class ARushPlayerController : public APlayerController, public ITeamAgentInterface, public ISelectorInterface
{
	GENERATED_BODY()

public:

	ARushPlayerController();
	void SetupInputComponent() override;

	void OnPressReleased();
	
	uint8 GetTeamId() override;

	void Select(ISelectableInterface* Selectable) override;
	void Unselect(ISelectableInterface* Selectable) override;
	ISelectableInterface* GetCurrentSelection() override;
	
	void TestAbility();

	const UAbility* GetAbility(TSubclassOf<UAbility> AbilityClass);
	bool IsAbilitySelected(TSubclassOf<UAbility> AbilityClass) const;
	void SelectAbility(TSubclassOf<UAbility> AbilityClass);
	void UnselectAbility();

private:

	UPROPERTY()
	TScriptInterface<ISelectableInterface> CurrentSelection;
	
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
