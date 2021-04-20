#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TsunamiTypes.h"
#include "TowerDefenseEssentialsInterface.generated.h"

UINTERFACE(Meta=(CannotImplementInterfaceInBlueprint))
class UTowerDefenseEssentialsInterface : public UInterface
{
	GENERATED_BODY()
};

class ITowerDefenseEssentialsInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual int32 GetHealth() { return -1; }

	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual void SubtractHealth(int32 Amount) {};

	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual int32 GetGoldCount() { return -1; }

	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual void AddGold(int32 Count) {}

	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual int32 GetCurrentWave() { return -1; }

	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual int32 GetTotalWaves() { return -1; }

	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual bool IsNextWaveQueued() { return false; }

	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual ETsunamiWaveStartMethod GetNextWaveStartMethod() { return ETsunamiWaveStartMethod::External; }

	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual float GetNextWaveStartTimeElapsedPercent() { return 0.5f; }

	UFUNCTION(BlueprintCallable, Category = "Tower Defense Essentials")
	virtual void StartNextWave() {}
};
