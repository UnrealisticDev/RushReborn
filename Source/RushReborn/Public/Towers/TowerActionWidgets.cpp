#include "TowerActionWidgets.h"
#include "TowerAction.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"

UTowerAction* UTowerActionWidget::GetAction() const
{
	return Action;
}

bool UTowerActionWidget::CanBeExecuted() const
{
	return Action->CanExecute(Context);
}

void UTowerActionWidget::Select()
{
	if (Action->RequiresConfirm())
	{
		if (bAwaitingConfirmation)
		{
			if (!Action->CanExecute(Context))
			{
				return;
			}

			Action->Unselect(Context);
			Action->Execute(Context);
			ActionExecuted.ExecuteIfBound(this);
		}

		else
		{
			bAwaitingConfirmation = true;
			Action->Select(Context);
			ActionSelected.ExecuteIfBound(this);
		}
	}

	else
	{
		Action->Execute(Context);
		ActionExecuted.ExecuteIfBound(this);
	}
}

void UTowerActionWidget::Unselect()
{
	bAwaitingConfirmation = false;
	Action->Unselect(Context);
}

void UTowerActionMenuWidget::PositionAction(UTowerActionWidget* ActionWidget, UCanvasPanelSlot* ActionSlot)
{
	UTowerAction* Action = ActionWidget->GetAction();
	const float MenuAngle = Action->GetMenuAngle();

	ActionSlot->SetAlignment(FVector2D(0.5f, 0.5f));
	ActionSlot->SetAnchors(FAnchors(0.5f, 0.5f, 0.5f, 0.5f));
	ActionSlot->SetAutoSize(true);
	ActionSlot->SetPosition(FVector2D
	(
		UKismetMathLibrary::DegCos(MenuAngle) * RadialOffset,
		UKismetMathLibrary::DegSin(MenuAngle) * RadialOffset * -1
	));
}

void UTowerActionMenuWidget::SetupActionObservers(UTowerActionWidget* ActionWidget)
{
	ActionWidget->ActionSelected.BindUObject(this, &UTowerActionMenuWidget::OnActionSelected);
	ActionWidget->ActionExecuted.BindUObject(this, &UTowerActionMenuWidget::OnActionExecuted);
}

void UTowerActionMenuWidget::OnActionSelected(UTowerActionWidget* SelectedActionWidget)
{
	WidgetTree->ForEachWidget([&SelectedActionWidget](UWidget* Widget)
	{
		if (UTowerActionWidget* ChildActionWidget = Cast<UTowerActionWidget>(Widget))
		{
			if (ChildActionWidget != SelectedActionWidget)
			{
				ChildActionWidget->Unselect();
			}
		}
	});

	WidgetTree->FindWidget<UTowerActionDetailsWidget>("Details")->Init(SelectedActionWidget->GetAction());
	WidgetTree->FindWidget<UTowerActionDetailsWidget>("Details")->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UTowerActionMenuWidget::OnActionExecuted(UTowerActionWidget* ExecutedActionWidget)
{
	Hide();
}

void UTowerActionMenuWidget::Hide_Implementation()
{
	WidgetTree->ForEachWidget([](UWidget* Widget)
	{
		if (UTowerActionWidget* ChildActionWidget = Cast<UTowerActionWidget>(Widget))
		{
			ChildActionWidget->Unselect();
		}
	});

	WidgetTree->FindWidget<UTowerActionDetailsWidget>("Details")->SetVisibility(ESlateVisibility::Hidden);
}
