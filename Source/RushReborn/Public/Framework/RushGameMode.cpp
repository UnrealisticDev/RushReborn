#include "RushGameMode.h"
#include "TsunamiEngine.h"
#include "TsunamiSequence.h"
#include "Player/RushPlayerController.h"
#include "Player/RushSpectatorPawn.h"

ARushGameMode::ARushGameMode()
{
	PlayerControllerClass = ARushPlayerController::StaticClass();
	DefaultPawnClass = ARushSpectatorPawn::StaticClass();

	Health = 20;
	Gold = 265;
	WaveEngine = CreateDefaultSubobject<UTsunamiEngine>(TEXT("WaveEngine"));
}

void ARushGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnSequence.IsValid())
	{
		UTsunamiSequence* LoadedSequence = Cast<UTsunamiSequence>(SpawnSequence.TryLoad());
		check(LoadedSequence);

		WaveEngine->MountSequence(LoadedSequence);
		WaveEngine->SequenceSpawnsDestroyed.AddDynamic(this, &ARushGameMode::Win);
	}
}

int32 ARushGameMode::GetHealth()
{
	return Health;
}

void ARushGameMode::SubtractHealth(int32 Amount)
{
	Health = FMath::Max(0, Health - Amount);
	if (Health == 0)
	{
		Lose();
	}
}

int32 ARushGameMode::GetGoldCount()
{
	return Gold;
}

void ARushGameMode::AddGold(int32 Count)
{
	Gold = FMath::Max(0, Gold + Count);
}

int32 ARushGameMode::GetCurrentWave()
{
	return WaveEngine->GetSequenceState().GetLastWaveStarted();
}

int32 ARushGameMode::GetTotalWaves()
{
	return WaveEngine->GetMountedSequence()->Waves.Num();
}

void ARushGameMode::StartNextWave()
{
	WaveEngine->ManuallyStartQueuedWave();
}

void ARushGameMode::Win()
{
	// @todo
}

void ARushGameMode::Lose()
{
	// @todo
}
