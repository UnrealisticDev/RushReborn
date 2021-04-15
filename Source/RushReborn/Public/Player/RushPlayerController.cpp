#include "RushPlayerController.h"
#include "Abilities/RainOfFireAbility.h"
#include "Abilities/ReinforcementsAbility.h"

void ARushPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction
	(
		"LeftMouseButton",
		IE_Released,
		this,
		&ARushPlayerController::TestAbility
	);
}

void ARushPlayerController::TestAbility()
{
	Reinforcements = NewObject<UReinforcementsAbility>(this);

	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, HitResult);

	FAbilityPayload Payload;
	Payload.Location = HitResult.Location;
	Reinforcements->Activate(Payload);
}
