#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TsunamiTypes.h"
#include "SpawnGate.generated.h"

class ASplineRepeater;
class UTsunamiSpawnGate;

/**
 * A SpawnGate is responsible for responding
 * to spawn requests from a TsunamiEngine and
 * directing spawned actors appropriately.
 *
 * As all spawns in this case are invaders,
 * the spawn gate spawns the requested class
 * and directs it to a random path to follow.
 */
UCLASS()
class ASpawnGate : public AActor
{
	GENERATED_BODY()

public:

	ASpawnGate();

	/** Callback to field spawn requests. */
	UFUNCTION()
	void Spawn(FTsunamiSpawnContext Context);

protected:

	/**
	 * This component registers itself as a spawn gate
	 * with the Tsunami system, at which point it can receive
	 * spawn requests.
	 */
	UPROPERTY(VisibleAnywhere)
	UTsunamiSpawnGate* SpawnGateComponent;

	/**
	 * Spline repeater to request invader paths from.
	 */
	UPROPERTY(EditAnywhere, Category = Spawn)
	ASplineRepeater* SpawnPaths;
};
