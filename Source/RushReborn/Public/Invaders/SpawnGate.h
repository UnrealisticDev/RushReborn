#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TsunamiTypes.h"
#include "SpawnGate.generated.h"

class ASplineRepeater;
class UTsunamiSpawnGate;

UCLASS()
class ASpawnGate : public AActor
{
	GENERATED_BODY()

public:

	ASpawnGate();

	UFUNCTION()
	void Spawn(FTsunamiSpawnContext Context);

protected:

	UPROPERTY(VisibleAnywhere)
	UTsunamiSpawnGate* SpawnGateComponent;

	UPROPERTY(EditAnywhere, Category = Spawn)
	ASplineRepeater* SpawnPaths;
};
