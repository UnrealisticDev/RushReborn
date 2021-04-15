#include "RushPlayerController.h"
#include "Abilities/RainOfFireAbility.h"
#include "Abilities/ReinforcementsAbility.h"

ARushPlayerController::ARushPlayerController()
{
	bShowMouseCursor = true;

	Reinforcements = CreateDefaultSubobject<UReinforcementsAbility>(TEXT("Reinforcements"));
	RainOfFire = CreateDefaultSubobject<URainOfFireAbility>(TEXT("Rain of Fire"));
}

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

const UAbility* ARushPlayerController::GetAbility(TSubclassOf<UAbility> AbilityClass)
{
	if (AbilityClass == UReinforcementsAbility::StaticClass())
	{
		return Reinforcements;
	}

	else if (AbilityClass == URainOfFireAbility::StaticClass())
	{
		return RainOfFire;
	}

	else
	{
		return nullptr;
	}
}

void ARushPlayerController::OnAbilitySelected(TSubclassOf<UAbility> AbilityClass)
{
	// @todo
}

void ARushPlayerController::OnAbilityUnselected(TSubclassOf<UAbility> AbilityClass)
{
	// @todo
}
