#include "AbilityWidget.h"
#include "Player/RushPlayerController.h"
#include "Ability.h"

void UAbilityWidget::NativeConstruct()
{
	CacheTargetAbility();

	Super::NativeConstruct();
}

bool UAbilityWidget::CanBeSelected() const
{
	if (TargetAbility.IsValid())
	{
		return !TargetAbility->IsOnCooldown();
	}

	else
	{
		return false;
	}
}

void UAbilityWidget::Select()
{
	bIsSelected = true;
	
	ARushPlayerController* RushPlayerController = Cast<ARushPlayerController>(GetOwningPlayer());
	check(RushPlayerController);
	RushPlayerController->OnAbilitySelected(TargetAbilityClass);

	OnSelected.Broadcast();
}

void UAbilityWidget::Unselect()
{
	bIsSelected = false;

	ARushPlayerController* RushPlayerController = Cast<ARushPlayerController>(GetOwningPlayer());
	check(RushPlayerController);
	RushPlayerController->OnAbilityUnselected(TargetAbilityClass);
}

void UAbilityWidget::CacheTargetAbility()
{
	ARushPlayerController* RushPlayerController = Cast<ARushPlayerController>(GetOwningPlayer());
	check(RushPlayerController);

	TargetAbility = RushPlayerController->GetAbility(TargetAbilityClass);
}
