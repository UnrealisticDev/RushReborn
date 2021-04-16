#include "RushPlayerController.h"
#include "Abilities/RainOfFireAbility.h"
#include "Abilities/ReinforcementsAbility.h"

ARushPlayerController::ARushPlayerController()
{
	bShowMouseCursor = true;

	Reinforcements = CreateDefaultSubobject<UReinforcementsAbility>(TEXT("Reinforcements"));
	RainOfFire = CreateDefaultSubobject<URainOfFireAbility>(TEXT("Rain of Fire"));

	SelectedAbility = EAbilitySelected::None;
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
	FHitResult HitResult;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, HitResult);

	FAbilityPayload Payload;
	Payload.Location = HitResult.Location;

	if (SelectedAbility == EAbilitySelected::Reinforcements)
	{
		SelectedAbility = EAbilitySelected::None;
		Reinforcements->Activate(Payload);
	}

	else if (SelectedAbility == EAbilitySelected::RainofFire)
	{
		SelectedAbility = EAbilitySelected::None;
		RainOfFire->Activate(Payload);
	}
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

bool ARushPlayerController::IsAbilitySelected(TSubclassOf<UAbility> AbilityClass) const
{
	return AbilityClass == UReinforcementsAbility::StaticClass() && SelectedAbility == EAbilitySelected::Reinforcements
		|| AbilityClass == URainOfFireAbility::StaticClass() && SelectedAbility == EAbilitySelected::RainofFire;
}

void ARushPlayerController::SelectAbility(TSubclassOf<UAbility> AbilityClass)
{
	if (AbilityClass == UReinforcementsAbility::StaticClass())
	{
		SelectedAbility = EAbilitySelected::Reinforcements;
	}

	else if (AbilityClass == URainOfFireAbility::StaticClass())
	{
		SelectedAbility = EAbilitySelected::RainofFire;
	}
}

void ARushPlayerController::UnselectAbility()
{
	SelectedAbility = EAbilitySelected::None;
}
