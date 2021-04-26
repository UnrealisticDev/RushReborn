#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

class AActor;
class UDamageType;
class AController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthDepleted);

/**
 * The Stats component contains a variety of
 * offensive, defensive, and movement-related stats
 * that to be used for different gameplay systems.
 * For example, it tracks health and emits an event
 * when health is depleted.
 * As another example, it hooks into its owning actor's damage event,
 * and uses armor and magic resistance to reduce incoming damage.
 * These stats can be used for any purpose deemed necessary
 * (like setting up tower attack patterns, or slowing enemies).
 */
UCLASS()
class UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UStatsComponent();
	void InitializeComponent() override;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(BlueprintAssignable)
	FHealthDepleted HealthDepleted;

	/** The maximum health this component can hold. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Defensive")
	float MaxHealth;

	/** The current health. */
	UPROPERTY(BlueprintReadOnly, Category = "Stats | Defensive")
	float CurrentHealth;

	/** Armor reduces physical damage. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Defensive")
	int32 Armor;

	/** Magic resistance reduces magical damage. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Defensive")
	int32 MagicResistance;

	/** A range of damage to apply on attack. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Offensive")
	FFloatRange AttackDamage;

	/** The frequency of attack. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Offensive")
	float AttackRate;

	/** The rate of movement. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Movement")
	float MovementSpeed;
};
