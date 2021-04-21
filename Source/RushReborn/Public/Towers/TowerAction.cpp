#include "TowerAction.h"

UTowerAction::UTowerAction()
	: Cost(-1)
{
	
}

FText UTowerAction::GetDisplayName() const
{
	return Name;
}

UTexture2D* UTowerAction::GetDisplayIcon() const
{
	return Icon;
}

float UTowerAction::GetMenuAngle()
{
	return MenuAngle;
}

int32 UTowerAction::GetCost() const
{
	return Cost;
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

bool UTowerAction::CanExecute(const FTowerActionContext& Context)
{
	return true;
}

void UTowerAction::Execute(const FTowerActionContext& Context)
{
	// no op
}
