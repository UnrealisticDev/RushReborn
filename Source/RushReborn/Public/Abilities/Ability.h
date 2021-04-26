#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ability.generated.h"

/**
 * The ability payload provides useful
 * targeting info during ability validation
 * and execution.
 *
 * This game only uses location-based targeting,
 * so this struct is very sparse. More complex
 * targeting schemes might benefit from adding
 * more fields here.
 */
USTRUCT()
struct FAbilityPayload
{
	GENERATED_BODY()

public:

	/** The targeted location. */
	UPROPERTY()
	FVector Location;
};

class UTexture2D;

/**
 * An ability is a global action that can be activated
 * by a player. Each ability must have a cooldown
 * and various display elements like a title and icon.
 *
 * The implementation of abilities is left to their
 * respective subclasses.
 */
UCLASS(Abstract)
class UAbility : public UObject
{
	GENERATED_BODY()

public:

	UAbility();

	/** Can this ability be activated? */
	virtual bool CanActivate(const FAbilityPayload& Payload);

	/**
	 * Activate this ability.
	 * Base implementation checks that ability is
	 * not on cooldown and then puts it on cooldown. 
	 */
	virtual void Activate(const FAbilityPayload& Payload);

	/** Returns true if the ability is on cooldown. */
	UFUNCTION(BlueprintPure, Category = "Status")
	bool IsOnCooldown() const;

	/** Get the cooldown of the ability. */
	UFUNCTION(BlueprintPure, Category = "Status")
	float GetCooldown() const;

	/** Get the elapsed cooldown of the ability. */
	UFUNCTION(BlueprintPure, Category = "Status")
	float GetCooldownElapsed() const;

	/** Get the remaining cooldown of the ability. */
	UFUNCTION(BlueprintPure, Category = "Status")
	float GetCooldownRemaining() const;

	/** Get the title of the ability. */
	UFUNCTION(BlueprintPure, Category = "Display")
	FText GetTitle() const;

	/** Get the description of the ability. */
	UFUNCTION(BlueprintPure, Category = "Display")
	FText GetDescription() const;

	/** Get the display icon of the ability. */
	UFUNCTION(BlueprintPure, Category = "Display")
	UTexture2D* GetIcon() const;

protected:

	/** Display title. */
	UPROPERTY()
	FText Title;

	/** Short form description (under 60 characters). */
	UPROPERTY()
	FText Description;

	/** Display icon. */
	UPROPERTY()
	UTexture2D* Icon;

	/** Minimum time between successive uses. */
	UPROPERTY()
	float Cooldown;

	/** Timer for tracking cooldown. */
	UPROPERTY()
	FTimerHandle CooldownTimer;
};
