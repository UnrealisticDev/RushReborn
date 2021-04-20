#include "TowerAction.h"

bool UTowerAction::CanSelect(const FTowerActionContext& Context)
{
	return true;
}

void UTowerAction::Select(const FTowerActionContext& Context)
{
	if (!bIsSelected)
	{
		bIsSelected = true;
		if (!bRequiresConfirm)
		{
			Execute(Context);
		}
	}

	else
	{
		if (bRequiresConfirm)
		{
			Execute(Context);
		}
	}
}

void UTowerAction::Unselect(const FTowerActionContext& Context)
{
	bIsSelected = false;
}

bool UTowerAction::IsSelected()
{
	return bIsSelected;
}

void UTowerAction::Execute(const FTowerActionContext& Context)
{
	// no op
}
