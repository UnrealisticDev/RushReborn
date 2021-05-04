#include "TowerAction_Rally.h"
#include "Kismet/GameplayStatics.h"
#include "Player/RushPlayerController.h"
#include "Towers/RallyCoordinatorInterface.h"
#include "Towers/Tower.h"
#include "Towers/TowerBerth.h"

UTowerAction_Rally::UTowerAction_Rally()
{
	bRequiresConfirm = false;
	Name = NSLOCTEXT("Tower Action Rally", "Rally Name", "Rally");
	Icon = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Game/Marketplace/PiP_Survival/Textures/Survival/64x64/T_Location_64x64.T_Location_64x64'")).Object;
	MenuAngle = 315.f;
}

void UTowerAction_Rally::Execute(const FTowerActionContext& Context)
{
	check(Context.TowerBerth.IsValid());
	check(Context.TowerBerth->GetTower());
	check(Context.TowerBerth->GetTower()->Implements<URallyCoordinatorInterface>());
	
	ARushPlayerController* RushPlayerController = Cast<ARushPlayerController>(Context.Selector.GetObject());
	if (RushPlayerController)
	{
		RushPlayerController->BeginTargetingRally(Context);
		UGameplayStatics::PlaySound2D(this, Cast<USoundBase>(ExecuteSound.TryLoad()), 0.5f);	
	}
}
