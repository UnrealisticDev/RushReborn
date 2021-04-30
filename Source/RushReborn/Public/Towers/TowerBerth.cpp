#include "TowerBerth.h"
#include "Tower.h"
#include "TowerActionWidgets.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/DecalComponent.h"
#include "Player/SelectorInterface.h"

ATowerBerth::ATowerBerth()
{
	InteractionZone = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionZone"));
	InteractionZone->SetSphereRadius(100.f);
	InteractionZone->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	SetRootComponent(InteractionZone);

	ActionMenu = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionMenu"));
	ActionMenu->SetupAttachment(GetRootComponent());

	RangeIndicatorDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("RangeIndicatorDecal"));
	RangeIndicatorDecal->SetupAttachment(GetRootComponent());
	RangeIndicatorDecal->SetVisibility(false);
	RangeIndicatorDecal->SetRelativeRotation(FRotator(-90, 0, 0));
	RangeIndicatorDecal->DecalSize.X = 15.f;
}

void ATowerBerth::OnSelected(ISelectorInterface* Selector)
{
	ShowActions(Selector);
	ShowRangeIndicator();
}

void ATowerBerth::OnUnselected(ISelectorInterface* Selector)
{
	HideActions();
	HideRangeIndicator();
}

ATower* ATowerBerth::GetTower() const
{
	return Tower;
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

void ATowerBerth::ShowRangeIndicator()
{
	if (Tower)
	{
		RangeIndicatorDecal->DecalSize.Y = Tower->GetInfluenceRadius();
		RangeIndicatorDecal->DecalSize.Z = Tower->GetInfluenceRadius();
		RangeIndicatorDecal->SetVisibility(true);
	}
}

void ATowerBerth::HideRangeIndicator()
{
	RangeIndicatorDecal->SetVisibility(false);
}
