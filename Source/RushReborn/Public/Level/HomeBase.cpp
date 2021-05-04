#include "HomeBase.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"
#include "Framework/TowerDefenseEssentialsInterface.h"
#include "Kismet/GameplayStatics.h"

void AHomeBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	OtherActor->Destroy();

	if (ITowerDefenseEssentialsInterface* EssentialsGameMode = Cast<ITowerDefenseEssentialsInterface>(GetWorld()->GetAuthGameMode()))
	{
		EssentialsGameMode->SubtractHealth(1);
	}

	UGameplayStatics::SpawnSound2D(this, Cast<USoundBase>(OverlapCue.TryLoad()));
}
