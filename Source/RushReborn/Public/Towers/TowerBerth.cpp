#include "TowerBerth.h"
#include "Components/SphereComponent.h"

ATowerBerth::ATowerBerth()
{
	InteractionZone = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionZone"));
	InteractionZone->SetSphereRadius(100.f);
	InteractionZone->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

void ATowerBerth::OnSelected(ISelectorInterface* Selector)
{
	
}

void ATowerBerth::OnUnselected(ISelectorInterface* Selector)
{
	// @todo
}
