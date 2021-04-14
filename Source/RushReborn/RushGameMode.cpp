#include "RushGameMode.h"
#include "Player/RushPlayerController.h"
#include "Player/RushSpectatorPawn.h"

ARushGameMode::ARushGameMode()
{
	PlayerControllerClass = ARushPlayerController::StaticClass();
	DefaultPawnClass = ARushSpectatorPawn::StaticClass();
}
