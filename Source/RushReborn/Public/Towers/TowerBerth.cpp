#include "TowerBerth.h"
#include "Tower.h"
#include "TowerActionWidgets.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Player/SelectorInterface.h"

ATowerBerth::ATowerBerth()
{
	InteractionZone = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionZone"));
	InteractionZone->SetSphereRadius(100.f);
	InteractionZone->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	SetRootComponent(InteractionZone);

	ActionMenu = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionMenu"));
	ActionMenu->SetupAttachment(GetRootComponent());
}

void ATowerBerth::OnSelected(ISelectorInterface* Selector)
{
	ShowActions(Selector);
}

void ATowerBerth::OnUnselected(ISelectorInterface* Selector)
{
	HideActions();
}

void ATowerBerth::SetTower(ATower* NewTower)
{
	Tower = NewTower;
}

void ATowerBerth::RemoveTower()
{
	Tower->Destroy();
	Tower = nullptr;
}

TArray<UTowerAction*> ATowerBerth::GetActions() const
{
	return Tower ? Tower->Actions : Actions;
}

void ATowerBerth::ShowActions(ISelectorInterface* Selector)
{
	FTowerActionContext Context;
	Context.TowerBerth = this;
	Context.Selector = Cast<UObject>(Selector);
	GetActionMenuWidget()->Show(GetActions(), Context);
}

void ATowerBerth::HideActions()
{
	GetActionMenuWidget()->Hide();
}

UTowerActionMenuWidget* ATowerBerth::GetActionMenuWidget() const
{
	return Cast<UTowerActionMenuWidget>(ActionMenu->GetWidget());
}
