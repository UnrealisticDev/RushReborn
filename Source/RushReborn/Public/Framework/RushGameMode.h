#pragma once

#include "CoreMinimal.h"
#include "TowerDefenseEssentialsInterface.h"
#include "GameFramework/GameModeBase.h"
#include "RushGameMode.generated.h"

class UOutcomeWidget;
class UTsunamiEngine;

/**
 * The RushGameMode is the primary gameplay
 * orchestrator for this demo. It is the host for
 * all essential global stats (e.g. health, gold)
 * and it is responsible for coordinating and tracking
 * spawning.
 */
UCLASS(Config=Game)
class RUSHREBORN_API ARushGameMode : public AGameModeBase, public ITowerDefenseEssentialsInterface
{
	GENERATED_BODY()
	
public:

	ARushGameMode();
	void BeginPlay() override;

	//~ Begin ITowerDefenseEssentialsInterface
	EGamePhase GetGamePhase() const override;
	int32 GetHealth() override;
	void SubtractHealth(int32 Amount) override;
	int32 GetGoldCount() override;
	void AddGold(int32 Count) override;
	int32 GetCurrentWave() override;
	int32 GetTotalWaves() override;
	bool IsNextWaveQueued() override;
	ETsunamiWaveStartMethod GetNextWaveStartMethod() override;
	float GetNextWaveStartTimeElapsedPercent() override;
	TMap<TSubclassOf<AActor>, int32> GetNextWaveStats() override;
	void StartNextWave() override;
	//~ End ITowerDefenseEssentialsInterface

	UFUNCTION()
	void OnWaveStarted(int32 Wave);
	
	UFUNCTION()
	void OnWaveAccelerated(int32 Wave, float TotalTime, float ElapsedTime);

	/** Called when the game is won. */
	UFUNCTION()
	void Win();

	/** Called when the game is lost. */
	UFUNCTION()
	void Lose();

	/** Stops all AI on game end. */
	void StopAllAI();
	
private:

	/** The current phase of the game. */
	UPROPERTY()
	EGamePhase Phase;

	/** Global health count. */
	UPROPERTY()
	int32 Health;

	/** Global gold count. */
	UPROPERTY()
	int32 Gold;

	/** Spawning engine. */
	UPROPERTY()
	UTsunamiEngine* WaveEngine;

	/** Spawn sequence to play. */
	UPROPERTY(Config)
	FSoftObjectPath SpawnSequence;

	/** Sound to play when a wave starts. */
	UPROPERTY(Config)
	FSoftObjectPath WaveStartSound;

	/** Widget to show final outcome. */
	UPROPERTY(Config)
	TSubclassOf<UOutcomeWidget> OutcomeWidgetClass;
};
