#include "TowerActionWidgets.h"
#include "TowerAction.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"

UTowerAction* UTowerActionWidget::GetAction() const
{
	return Action;
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
	//
}

void UTowerActionMenuWidget::Hide_Implementation()
{
	
}
