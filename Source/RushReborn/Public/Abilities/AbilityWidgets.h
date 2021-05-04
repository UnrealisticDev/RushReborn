#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityWidgets.generated.h"

class UAbility;

/**
 * An AbilityWidget represents a player's
 * global ability such as Rain of Fire or Reinforcements.
 * It caches the target ability on construct and
 * provides blueprint-callable utilities for
 * selecting and unselecting the ability.
 *
 * This widget depends on the owning player
 * being a RushPlayerController.
 */
UCLASS(Blueprintable)
class UAbilityWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;

	/** Can this ability be selected. */
	UFUNCTION(BlueprintPure)
	bool CanBeSelected() const;

	/** Returns true if the ability is selected. */
	UFUNCTION(BlueprintPure)
	bool IsSelected() const;

	/** Select this ability. */
	UFUNCTION(BlueprintCallable)
	void Select();

	/** Unselect this ability. */
	UFUNCTION(BlueprintCallable)
	void Unselect();

private:

	/** Caches target ability from player based on target class. */
	void CacheTargetAbility();

	/** The ability class to watch. */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAbility> TargetAbilityClass;

	/** The target ability to watch. */
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TWeakObjectPtr<const UAbility> TargetAbility;
};

/** Displays details of an ability. */
UCLASS(Blueprintable)
class UAbilityDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** Get the currently selected ability, if any. */
	UFUNCTION(BlueprintPure, Category = Ability)
	UAbility* GetSelectedAbility() const;
};
