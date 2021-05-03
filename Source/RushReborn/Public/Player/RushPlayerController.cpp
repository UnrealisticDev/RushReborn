#include "RushPlayerController.h"
#include "SelectableInterface.h"
#include "Abilities/RainOfFireAbility.h"
#include "Abilities/ReinforcementsAbility.h"
#include "Blueprint/UserWidget.h"
#include "Combat/Teams.h"
#include "Towers/RallyCoordinatorInterface.h"
#include "Towers/TowerBerth.h"
#include "Towers/Tower.h"
#include "Engine/DecalActor.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Components/DecalComponent.h"
#include "Framework/Commands/InputChord.h"

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

	FInputKeyBinding RainOfFireBinding;
	RainOfFireBinding.Chord.Key = EKeys::One;
	RainOfFireBinding.KeyDelegate = FInputActionHandlerSignature::CreateUObject(this, &ARushPlayerController::SelectAbility, TSubclassOf<UAbility>(URainOfFireAbility::StaticClass()));
	InputComponent->KeyBindings.Emplace(MoveTemp(RainOfFireBinding));

	FInputKeyBinding ReinforcementsBinding;
	ReinforcementsBinding.Chord.Key = EKeys::Two;
	ReinforcementsBinding.KeyDelegate = FInputActionHandlerSignature::CreateUObject(this, &ARushPlayerController::SelectAbility, TSubclassOf<UAbility>(UReinforcementsAbility::StaticClass()));
	InputComponent->KeyBindings.Emplace(MoveTemp(ReinforcementsBinding));	
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
			SetInputState(EInputState::Free);
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
			SetInputState(EInputState::Free);
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
		|| AbilityClass == URainOfFireAbility::StaticClass() && SelectedAbility == EAbilitySelected::RainOfFire);
}

void ARushPlayerController::SelectAbility(TSubclassOf<UAbility> AbilityClass)
{
	HideTargetActor();

	if (InputState != EInputState::TargetingAbility)
	{
		if (AbilityClass == UReinforcementsAbility::StaticClass())
		{
			SelectedAbility = EAbilitySelected::Reinforcements;
		}

		else if (AbilityClass == URainOfFireAbility::StaticClass())
		{
			SelectedAbility = EAbilitySelected::RainOfFire;
		}

		SetInputState(EInputState::TargetingAbility);
		Unselect(GetCurrentSelection());
	}

	else
	{
		if (AbilityClass == UReinforcementsAbility::StaticClass())
		{
			if (SelectedAbility == EAbilitySelected::Reinforcements)
			{
				UnselectAbility();
				return;
			}

			else
			{
				SelectedAbility = EAbilitySelected::Reinforcements;
				ShowTargetActor();
			}
		}

		else if (AbilityClass == URainOfFireAbility::StaticClass())
		{
			if (SelectedAbility == EAbilitySelected::RainOfFire)
			{
				UnselectAbility();
				return;
			}

			else
			{
				SelectedAbility = EAbilitySelected::RainOfFire;
				ShowTargetActor();
			}
		}
	}
}

void ARushPlayerController::UnselectAbility()
{
	SetInputState(EInputState::Free);
}

void ARushPlayerController::BeginTargetingRally(const FTowerActionContext& RallyContext)
{
	SetInputState(EInputState::TargetingRally);

	TowerActionContext = RallyContext;
}

void ARushPlayerController::ShowTargetActor()
{
	TargetActor = GetWorld()->SpawnActor<ADecalActor>();
	ConfigureTargetActor();
	GetWorld()->GetTimerManager().SetTimer(TargetUpdateTimer, this, &ARushPlayerController::UpdateTargetActor, .03f, true);
}

void ARushPlayerController::ConfigureTargetActor()
{
	switch (InputState)
	{
	case EInputState::TargetingAbility:
		switch (SelectedAbility)
		{
		case EAbilitySelected::Reinforcements:
			TargetActor->GetDecal()->DecalSize.Y = TargetActor->GetDecal()->DecalSize.Z = 125.f;
			TargetActor->SetDecalMaterial(Cast<UMaterialInterface>(ReinforcementsTargetMaterial.TryLoad()));
			break;
		case EAbilitySelected::RainOfFire:
			TargetActor->GetDecal()->DecalSize.Y = TargetActor->GetDecal()->DecalSize.Z = 500.f;
			TargetActor->SetDecalMaterial(Cast<UMaterialInterface>(RainOfFireTargetMaterial.TryLoad()));
			break;
		default: 
			break;
		}
		break;
	case EInputState::TargetingRally:
		TargetActor->SetDecalMaterial(Cast<UMaterialInterface>(RallyTargetMaterial.TryLoad()));
		break;
	case EInputState::Free:
	default:
		break;
	}
}

void ARushPlayerController::UpdateTargetActor()
{
	FHitResult Hit;
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility), false, Hit);

	if (Hit.IsValidBlockingHit())
	{
		TargetActor->SetActorLocation(Hit.Location);
	}
}

void ARushPlayerController::HideTargetActor()
{
	if (TargetActor)
	{
		TargetActor->Destroy();
		GetWorld()->GetTimerManager().ClearTimer(TargetUpdateTimer);
	}
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

void ARushPlayerController::SetInputState(EInputState NewState)
{
	InputState = NewState;

	switch (InputState)
	{
	case EInputState::Free:
		HideTargetActor();
		break;
	case EInputState::TargetingAbility:
	case EInputState::TargetingRally:
		ShowTargetActor();
		break;
	default: 
		break;
	}
}
