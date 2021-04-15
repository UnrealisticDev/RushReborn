#include "ReinforcementsAbility.h"

UReinforcementsAbility::UReinforcementsAbility()
	: SpawnOffset(50.f, -50.f, 0.f)
{
	Title = NSLOCTEXT("Reinforcements", "Reinforcements Title", "Call Reinforcements");
	Title = NSLOCTEXT("Reinforcements", "Reinforcements Description", "To block and fight enemies.");
	Cooldown = 10.f;
}

void UReinforcementsAbility::Activate(const FAbilityPayload& Payload)
{
	Super::Activate(Payload);

	check(SpawnClass.IsValid());

	FVector TargetLocation = Payload.Location;
	GetWorld()->SpawnActor<AActor>(SpawnClass.TryLoadClass<AActor>(), TargetLocation + SpawnOffset, FRotator::ZeroRotator);
	GetWorld()->SpawnActor<AActor>(SpawnClass.TryLoadClass<AActor>(), TargetLocation + (SpawnOffset * -1), FRotator::ZeroRotator);
}

