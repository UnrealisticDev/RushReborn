#include "SpawnGate.h"
#include "SplineRepeater.h"
#include "TsunamiEngine.h"
#include "TsunamiSpawnComponents.h"
#include "Components/SplineComponent.h"
#include "Characters/SplineFollowInterface.h"

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

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	AActor* SpawnedActor = GetWorld()->SpawnActorAbsolute(Context.SpawnClass, ChosenPath->GetTransformAtSplinePoint(0, ESplineCoordinateSpace::World), Params);
	if (ISplineFollowInterface* SpawnedSplineFollower = Cast<ISplineFollowInterface>(SpawnedActor))
	{
		SpawnedSplineFollower->SetSplineToFollow(ChosenPath);
	}

	Context.Engine->PostSpawn(SpawnedActor, Context);
}
