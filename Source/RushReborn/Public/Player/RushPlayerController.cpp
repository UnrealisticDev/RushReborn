#include "RushPlayerController.h"
#include "Abilities/RainOfFireAbility.h"

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
	RainOfFire = NewObject<URainOfFireAbility>(this);

	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, HitResult);

	FAbilityPayload Payload;
	Payload.Location = HitResult.Location;
	RainOfFire->Activate(Payload);
}
