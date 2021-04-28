#include "RushPlayerController.h"
#include "SelectableInterface.h"
#include "Abilities/RainOfFireAbility.h"
#include "Abilities/ReinforcementsAbility.h"
#include "Blueprint/UserWidget.h"
#include "Combat/Teams.h"
#include "Towers/RallyCoordinatorInterface.h"
#include "Towers/TowerBerth.h"
#include "Towers/Tower.h"

ARushPlayerController::ARushPlayerController()
{
	bShowMouseCursor = true;

	Reinforcements = CreateDefaultSubobject<UReinforcementsAbility>(TEXT("Reinforcements"));
	RainOfFire = CreateDefaultSubobject<URainOfFireAbility>(TEXT("Rain of Fire"));

	InputState = EInputState::Free;
}

void ARushPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction
	(
		"LeftMouseButton",
		IE_Released,
		this,
		&ARushPlayerController::OnPressReleased
	);
}

void ARushPlayerController::OnPressReleased()
{
	FHitResult HitUnderCursor;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), false, HitUnderCursor);

	if (InputState == EInputState::Free)
	{
		Unselect(Cast<ISelectableInterface>(CurrentSelection.GetObject()));

		if (ISelectableInterface* HitSelectable = Cast<ISelectableInterface>(HitUnderCursor.GetActor()))
		{
			Select(HitSelectable);
		}
	}

	else if (InputState == EInputState::TargetingAbility)
	{
		FAbilityPayload Payload;
		Payload.Location = HitUnderCursor.Location;

		UAbility* RelevantAbility = SelectedAbility == EAbilitySelected::Reinforcements ? Reinforcements : RainOfFire;
		if (RelevantAbility->CanActivate(Payload))
		{
			RelevantAbility->Activate(Payload);
			InputState = EInputState::Free;
		}

		else
		{
			IndicateBadLocation(HitUnderCursor.Location);
		}
	}
	
	else if (InputState == EInputState::TargetingRally)
	{
		IRallyCoordinatorInterface* RallyingTower = Cast<IRallyCoordinatorInterface>(TowerActionContext.TowerBerth->GetTower());
		if (RallyingTower && RallyingTower->CanRally(HitUnderCursor.Location))
		{
			RallyingTower->Rally(HitUnderCursor.Location);
			Unselect(TowerActionContext.TowerBerth.Get());
			InputState = EInputState::Free;
		}

		else
		{
			IndicateBadLocation(HitUnderCursor.Location);
		}
	}
}

uint8 ARushPlayerController::GetTeamId()
{
	return (uint8)ETeams::Defender;
}

void ARushPlayerController::Select(ISelectableInterface* Selectable)
{
	CurrentSelection = Cast<UObject>(Selectable);
	CurrentSelection->OnSelected(this);
}

void ARushPlayerController::Unselect(ISelectableInterface* Selectable)
{
	if (Selectable && CurrentSelection == Selectable)
	{
		CurrentSelection = nullptr;
		Selectable->OnUnselected(this);
	}
}

ISelectableInterface* ARushPlayerController::GetCurrentSelection()
{
	return Cast<ISelectableInterface>(CurrentSelection.GetObject());
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
	return InputState == EInputState::TargetingAbility
	&& (AbilityClass == UReinforcementsAbility::StaticClass() && SelectedAbility == EAbilitySelected::Reinforcements
		|| AbilityClass == URainOfFireAbility::StaticClass() && SelectedAbility == EAbilitySelected::RainofFire);
}

void ARushPlayerController::SelectAbility(TSubclassOf<UAbility> AbilityClass)
{
	InputState = EInputState::TargetingAbility;
	
	if (AbilityClass == UReinforcementsAbility::StaticClass())
	{
		SelectedAbility = EAbilitySelected::Reinforcements;
	}

	else if (AbilityClass == URainOfFireAbility::StaticClass())
	{
		SelectedAbility = EAbilitySelected::RainofFire;
	}

	Unselect(GetCurrentSelection());
}

void ARushPlayerController::UnselectAbility()
{
	InputState = EInputState::Free;
}

void ARushPlayerController::BeginTargetingRally(const FTowerActionContext& RallyContext)
{
	InputState = EInputState::TargetingRally;

	TowerActionContext = RallyContext;
}

void ARushPlayerController::IndicateBadLocation(FVector Location)
{
	if (BadLocationWidgetClass.IsValid())
	{
		UUserWidget* BadLocationWidget = CreateWidget<UUserWidget>(this, BadLocationWidgetClass.TryLoadClass<UUserWidget>());
		if (BadLocationWidget)
		{
			FVector2D ScreenLocation;
			ProjectWorldLocationToScreen(Location, ScreenLocation);

			FIntVector ViewportSize;
			GetViewportSize(ViewportSize.X, ViewportSize.Y);

			BadLocationWidget->AddToViewport();
			BadLocationWidget->SetPositionInViewport(ScreenLocation);
		}
	}
}
