#include "TowerAction.h"
#include "Player/SelectorInterface.h"
#include "TowerBerth.h"

UTowerAction::UTowerAction()
	: Cost(-1)
{
	
}

FText UTowerAction::GetDisplayName() const
{
	return Name;
}

FText UTowerAction::GetDescription() const
{
	return Description;
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

bool UTowerAction::RequiresConfirm() const
{
	return bRequiresConfirm;
}

void UTowerAction::Select(const FTowerActionContext& Context)
{
	// no op
}

void UTowerAction::Unselect(const FTowerActionContext& Context)
{
	// no op
}

bool UTowerAction::CanExecute(const FTowerActionContext& Context)
{
	return true;
}

void UTowerAction::Execute(const FTowerActionContext& Context)
{
	// no op
}

void UTowerAction::UnselectTowerBerth(const FTowerActionContext& Context)
{
	if (Context.TowerBerth.IsValid() && Context.Selector)
	{
		Context.Selector->Unselect(Context.TowerBerth.Get());
	}
}
