#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityWidget.generated.h"

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

	UFUNCTION(BlueprintPure)
	bool CanBeSelected() const;

	UFUNCTION(BlueprintPure)
	bool IsSelected() const;

	UFUNCTION(BlueprintCallable)
	void Select();

	UFUNCTION(BlueprintCallable)
	void Unselect();

private:

	void CacheTargetAbility();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAbility> TargetAbilityClass;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TWeakObjectPtr<const UAbility> TargetAbility;
};
