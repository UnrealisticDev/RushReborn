#include "TowerAction_Sell.h"
#include "TowerBerth.h"
#include "Framework/TowerDefenseEssentialsInterface.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"

UTowerAction_Sell::UTowerAction_Sell()
	: SetupValue(50)
	, SpawningValue(50)
{
	bRequiresConfirm = true;
}

void UTowerAction_Sell::Execute(const FTowerActionContext& Context)
{
	Context.TowerBerth->RemoveTower();
	if (ITowerDefenseEssentialsInterface* EssentialsGameMode = Cast<ITowerDefenseEssentialsInterface>(GetWorld()->GetAuthGameMode()))
	{
		EssentialsGameMode->AddGold
		(
			EssentialsGameMode->GetGamePhase() == EGamePhase::Setup
			? SetupValue
			: SpawningValue
		);
	}

	UnselectTowerBerth(Context);
}
