#include "TowerAction_Rally.h"
#include "Player/RushPlayerController.h"
#include "Towers/RallyCoordinatorInterface.h"
#include "Towers/Tower.h"
#include "Towers/TowerBerth.h"

UTowerAction_Rally::UTowerAction_Rally()
{
	bRequiresConfirm = false;
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
	}
}
