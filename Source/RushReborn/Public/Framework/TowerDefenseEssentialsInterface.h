#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TsunamiTypes.h"
#include "TowerDefenseEssentialsInterface.generated.h"

class AActor;

/** The phases of the game. */
UENUM()
enum class EGamePhase : uint8
{
	Setup,
	Spawning,
	Complete
};

/**
 * Exposes a host of standard tower defense stats
 * and functionality, including health, gold, and
 * wave management.
 *
 * This allows UI to query common information without
 * concern for the specific game mode class that is
 * currently active.
 */
UINTERFACE(Meta=(CannotImplementInterfaceInBlueprint))
class UTowerDefenseEssentialsInterface : public UInterface
{
	GENERATED_BODY()
};

class ITowerDefenseEssentialsInterface
{
	GENERATED_BODY()

public:

	/** Get the current phase of the game. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual EGamePhase GetGamePhase() const { return EGamePhase::Setup; }

	/** Get the global health amount. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual int32 GetHealth() { return -1; }

	/** Reduce global health. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual void SubtractHealth(int32 Amount) {};

	/** Get the global gold count. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual int32 GetGoldCount() { return -1; }

	/** Add gold (can be negative). */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual void AddGold(int32 Count) {}

	/** Get the current spawn wave index. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual int32 GetCurrentWave() { return -1; }

	/** Get the total number of spawn waves. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual int32 GetTotalWaves() { return -1; }

	/** Returns true if the next wave is queued. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual bool IsNextWaveQueued() { return false; }

	/** Get the start method for the currently queued wave. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual ETsunamiWaveStartMethod GetNextWaveStartMethod() { return ETsunamiWaveStartMethod::External; }

	/** Get the percentage of time remaining until the next wave starts. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual float GetNextWaveStartTimeElapsedPercent() { return 0.5f; }

	/** Get a list of spawned actors and their respective counts for the next wave. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual TMap<TSubclassOf<AActor>, int32> GetNextWaveStats() {return TMap<TSubclassOf<AActor>, int32>();}

	/** Start the next wave manually. */
	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual void StartNextWave() {}
};
