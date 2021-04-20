#include "SpawnGate.h"
#include "SplineRepeater.h"
#include "TsunamiSpawnComponents.h"
#include "Components/SplineComponent.h"

ASpawnGate::ASpawnGate()
{
	SpawnGateComponent = CreateDefaultSubobject<UTsunamiSpawnGate>(TEXT("Spawn Gate Component"));
	SpawnGateComponent->Spawn.AddDynamic(this, &ASpawnGate::Spawn);
}

void ASpawnGate::Spawn(FTsunamiSpawnContext Context)
{
	check(SpawnPaths);

	TArray<USplineComponent*> PossiblePaths = SpawnPaths->GetSplines();
	USplineComponent* ChosenPath = PossiblePaths[FMath::Rand() % PossiblePaths.Num()];

	AActor* SpawnedActor = GetWorld()->SpawnActorAbsolute(Context.SpawnClass, ChosenPath->GetTransformAtSplinePoint(0, ESplineCoordinateSpace::World));
	if (SpawnedActor)
	{
		// @todo: set path on actor
	}
}
