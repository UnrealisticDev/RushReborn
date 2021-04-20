#pragma once

#include "CoreMinimal.h"
#include "TowerDefenseEssentialsInterface.h"
#include "GameFramework/GameModeBase.h"
#include "RushGameMode.generated.h"

class UTsunamiEngine;
class UTsunamiSequence;

/**
 * 
 */
UCLASS(Config=Game)
class RUSHREBORN_API ARushGameMode : public AGameModeBase, public ITowerDefenseEssentialsInterface
{
	GENERATED_BODY()
	
public:

	ARushGameMode();
	void BeginPlay() override;

	int32 GetHealth() override;
	void SubtractHealth(int32 Amount) override;
	int32 GetGoldCount() override;
	void AddGold(int32 Count) override;
	virtual int32 GetCurrentWave() override;
	virtual int32 GetTotalWaves() override;
	virtual bool IsNextWaveQueued() override;
	virtual ETsunamiWaveStartMethod GetNextWaveStartMethod() override;
	virtual float GetNextWaveStartTimeElapsedPercent() override;
	virtual void StartNextWave() override;

	UFUNCTION()
	void Win();

	UFUNCTION()
	void Lose();
	
private:

	UPROPERTY()
	int32 Health;
	
	UPROPERTY()
	int32 Gold;

	UPROPERTY()
	UTsunamiEngine* WaveEngine;

	UPROPERTY(Config)
	FSoftObjectPath SpawnSequence;
};
