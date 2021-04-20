#include "HomeBase.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenseEssentialsInterface.h"
#include "Engine/World.h"

void AHomeBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
	OtherActor->Destroy();

	if (ITowerDefenseEssentialsInterface* EssentialsGameMode = Cast<ITowerDefenseEssentialsInterface>(GetWorld()->GetAuthGameMode()))
	{
		EssentialsGameMode->SubtractHealth(1);
	}
}
