#include "TowerAction_Rally.h"
#include "Player/RushPlayerController.h"

UTowerAction_Rally::UTowerAction_Rally()
{
	bRequiresConfirm = false;
}

void UTowerAction_Rally::Execute(const FTowerActionContext& Context)
{
	ARushPlayerController* RushPlayerController = Cast<ARushPlayerController>(Context.Selector.GetObject());
	if (RushPlayerController)
	{
		RushPlayerController->BeginTargetingRally(Context);
	}
}
