#include "TowerAction_Sell.h"
#include "Towers/TowerBerth.h"
#include "Framework/TowerDefenseEssentialsInterface.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

UTowerAction_Sell::UTowerAction_Sell()
	: SetupValue(50)
	, SpawningValue(50)
{
	bRequiresConfirm = true;
	Name = NSLOCTEXT("Tower Action Sell", "Sell Name", "Sell");
	Icon = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Game/Marketplace/PiP_Survival/Textures/Survival/64x64/T_Toothwheel_64x64.T_Toothwheel_64x64'")).Object;
	MenuAngle = 270.f;
}

FText UTowerAction_Sell::GetDescription() const
{
	if (ITowerDefenseEssentialsInterface* EssentialsGameMode = Cast<ITowerDefenseEssentialsInterface>(GetWorld()->GetAuthGameMode()))
	{
		return FText::Format
		(
			NSLOCTEXT("Tower Action Sell", "Sell Description", "Sell this tower and get a {0} GP refund."),
			EssentialsGameMode->GetGamePhase() == EGamePhase::Setup ? SetupValue : SpawningValue
		);
	}

	else
	{
		return Description;
	}
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

	UGameplayStatics::PlaySound2D(this, Cast<USoundBase>(ExecuteSound.TryLoad()), 0.5f);

	UnselectTowerBerth(Context);
}
