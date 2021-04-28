#include "ReinforcementsAbility.h"
#include "UObject/ConstructorHelpers.h"

UReinforcementsAbility::UReinforcementsAbility()
	: SpawnOffset(150.f, -150.f, 0.f)
{
	Title = NSLOCTEXT("Reinforcements", "Reinforcements Title", "Call Reinforcements");
	Description = NSLOCTEXT("Reinforcements", "Reinforcements Description", "To block and fight enemies.");
	Icon = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Game/Marketplace/PiP_Survival/Textures/Survival/256x256/T_Axe_256x256.T_Axe_256x256'")).Object;
	Cooldown = 10.f;
}

bool UReinforcementsAbility::CanActivate(const FAbilityPayload& Payload)
{
	FHitResult HitTargetingZone;
	GetWorld()->LineTraceSingleByChannel
	(
		HitTargetingZone, 
		Payload.Location + FVector(0, 0, 100.f), 
		Payload.Location + FVector(0, 0, -100.f),
		ECollisionChannel::ECC_GameTraceChannel1 /* Targeting */
	);

	return HitTargetingZone.IsValidBlockingHit();
}

void UReinforcementsAbility::Activate(const FAbilityPayload& Payload)
{
	Super::Activate(Payload);

	check(SpawnClass.IsValid());

	FVector TargetLocation = Payload.Location;
	GetWorld()->SpawnActor<AActor>(SpawnClass.TryLoadClass<AActor>(), TargetLocation + SpawnOffset, FRotator::ZeroRotator);
	GetWorld()->SpawnActor<AActor>(SpawnClass.TryLoadClass<AActor>(), TargetLocation + (SpawnOffset * -1), FRotator::ZeroRotator);
}

