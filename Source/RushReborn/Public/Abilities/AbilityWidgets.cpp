#include "AbilityWidgets.h"
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

bool UAbilityWidget::IsSelected() const
{
	ARushPlayerController* RushPlayerController = Cast<ARushPlayerController>(GetOwningPlayer());
	check(RushPlayerController);

	return RushPlayerController->IsAbilitySelected(TargetAbilityClass);
}

void UAbilityWidget::Select()
{
	ARushPlayerController* RushPlayerController = Cast<ARushPlayerController>(GetOwningPlayer());
	check(RushPlayerController);

	RushPlayerController->SelectAbility(TargetAbilityClass);
}

void UAbilityWidget::Unselect()
{
	ARushPlayerController* RushPlayerController = Cast<ARushPlayerController>(GetOwningPlayer());
	check(RushPlayerController);

	RushPlayerController->UnselectAbility();
}

void UAbilityWidget::CacheTargetAbility()
{
	ARushPlayerController* RushPlayerController = Cast<ARushPlayerController>(GetOwningPlayer());
	check(RushPlayerController);

	TargetAbility = RushPlayerController->GetAbility(TargetAbilityClass);
}

UAbility* UAbilityDetailsWidget::GetSelectedAbility() const
{
	return GetOwningPlayer()->IsA<ARushPlayerController>() ? const_cast<UAbility*>(Cast<ARushPlayerController>(GetOwningPlayer())->GetSelectedAbility()) : nullptr;
}
