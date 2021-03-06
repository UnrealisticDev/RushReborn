#pragma once

#include "CoreMinimal.h"
#include "SelectorInterface.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/PlayerController.h"
#include "Towers/TowerActionContext.h"
#include "RushPlayerController.generated.h"

class ADecalActor;
class ISelectableInterface;
class UAbility;

/**
 * The RushPlayerController is the hub for all
 * player input in this demo. Among other things,
 * it manages input state in order to properly direct
 * clicks (i.e. activate ability if targeting ability,
 * else select target under cursor).
 */
UCLASS(Config=Game)
class ARushPlayerController : public APlayerController, public ITeamAgentInterface, public ISelectorInterface
{
	GENERATED_BODY()

public:

	ARushPlayerController();
	void SetupInputComponent() override;

	void OnPressReleased();

	//~ Begin ITeamAgentInterface
	uint8 GetTeamId() override;
	//~ End ITeamAgentInterface

	//~ Begin ISelectorInterface
	void Select(ISelectableInterface* Selectable) override;
	void Unselect(ISelectableInterface* Selectable) override;
	ISelectableInterface* GetCurrentSelection() override;
	//~ End ISelectorInterface

	/** Get the first ability instance for the specified class, if it exists. */
	const UAbility* GetAbility(TSubclassOf<UAbility> AbilityClass);

	/** Returns true if the ability matching the specified class is selected. */
	bool IsAbilitySelected(TSubclassOf<UAbility> AbilityClass) const;

	/** Get the currently selected ability, if any. */
	const UAbility* GetSelectedAbility() const;

	/** Select the first ability instance for the specified class, if it exists. */
	void SelectAbility(TSubclassOf<UAbility> AbilityClass);

	/** Unselect the first ability instance for the specified, if it exists. */
	void UnselectAbility();

	/** Start targeting the rally tower action. */
	void BeginTargetingRally(const FTowerActionContext& RallyContext);

private:

	/** Targeting UI functions. */
	void ShowTargetActor();
	void ConfigureTargetActor();
	void UpdateTargetActor();
	void HideTargetActor();

	/** Actor used to display targeting information. */
	UPROPERTY()
	ADecalActor* TargetActor;

	/** Timer to update location of target actor. */
	UPROPERTY()
	FTimerHandle TargetUpdateTimer;

	/** Decal material for reinforcements targeting. */
	UPROPERTY(Config)
	FSoftObjectPath ReinforcementsTargetMaterial;

	/** Decal material for rain of fire targeting. */
	UPROPERTY(Config)
	FSoftObjectPath RainOfFireTargetMaterial;
	
	/** Decal material for rally targeting. */
	UPROPERTY(Config)
	FSoftObjectPath RallyTargetMaterial;
	
	/** Shows UI to indicate bad location for targeted event. */
	void IndicateBadLocation(FVector Location);

	/** The input states that this controller can be in. */
	enum class EInputState : uint8
	{
		Free,
		TargetingAbility,
		TargetingRally
	};

	/** The current input state. */
	EInputState InputState;

	/** Central facility to set input state. */
	void SetInputState(EInputState NewState);

	/** The current selection. */
	UPROPERTY()
	TScriptInterface<ISelectableInterface> CurrentSelection;

	/** An instance of the Reinforcements ability. */
	UPROPERTY()
	UAbility* Reinforcements;

	/** An instance of the Rain of Fire ability. */
	UPROPERTY()
	UAbility* RainOfFire;

	/** The possible ability selections. */
	enum class EAbilitySelected : uint8
	{
		Reinforcements,
		RainOfFire
	};

	/** The currently selected ability. */
	EAbilitySelected SelectedAbility;

	/** Context for the current tower action. */
	UPROPERTY()
	FTowerActionContext TowerActionContext;

	/** Widget to show when bad location selected. */
	UPROPERTY(Config)
	FSoftClassPath BadLocationWidgetClass;
};
