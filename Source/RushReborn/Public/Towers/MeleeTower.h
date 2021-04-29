#pragma once

#include "CoreMinimal.h"
#include "RallyCoordinatorInterface.h"
#include "Tower.h"
#include "Components/ActorComponent.h"
#include "MeleeTower.generated.h"

/**
 * Minimal component that emits an event when
 * owning actor is destroyed.
 */
UCLASS()
class USoldierDeathTracker : public UActorComponent
{
	GENERATED_BODY()

public:

	USoldierDeathTracker();
	
	void InitializeComponent() override;
	void UninitializeComponent() override;

	/** Called when owning actor is destroyed. */
	FSimpleDelegate Died;
};

/**
 * The MeleeTower is the base class
 * for the militia barracks. It supports
 * respawning and rallying.
 */
UCLASS()
class AMeleeTower : public ATower, public IRallyCoordinatorInterface
{
	GENERATED_BODY()

public:

	AMeleeTower();

	void BeginPlay() override;

protected:

	/** Get the location to spawn soldiers at. */
	UFUNCTION(BlueprintImplementableEvent, Category = Spawn)
	FVector GetSpawnPoint() const;

private:
	
	/** Sets a default rallying point. */
	void SetStartingRallyPoint();

	/**
	 * Calculates home location for soldier based
	 * on index and relative to rally point.
	 */
	FVector CalculateHomeLocation(int32 Index);

	/** Spawn and track a soldier. */
	void SpawnSoldier(int32 Index);

	/** Called when a soldier dies. */
	void OnSoldierDied(int32 Index);

	//~ Begin IRallyCoordinatorInterface
	bool CanRally(FVector NewRallyPoint) const override;
	void Rally(FVector NewRallyPoint) override;
	//~ End IRallyCoordinatorInterface
	
	void Destroyed() override;

protected:

	/** The area within which soldiers can be rallied. */
	UPROPERTY(EditAnywhere, Category = Influence)
	float InfluenceRadius;

	/** The soldier class to spawn. */
	UPROPERTY(EditAnywhere, Category = Soldier)
	TSubclassOf<AActor> SoldierClass;

	/** Current rally point. */
	UPROPERTY()
	FVector RallyPoint;

	/** How far from rally point to position soldiers. */
	UPROPERTY(EditAnywhere, Category = Rally)
	float RallyOffset;

	/** List of soldiers. */
	TWeakObjectPtr<APawn> Soldiers[3];

	/** Whether this tower is being manually destroyed. */
	UPROPERTY()
	bool bManualDestroy;
};
