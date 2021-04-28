#include "RushGameMode.h"
#include "TsunamiEngine.h"
#include "TsunamiSequence.h"
#include "Player/RushPlayerController.h"
#include "Player/RushSpectatorPawn.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "TsunamiBlueprintLibrary.h"

ARushGameMode::ARushGameMode()
	: Phase(EGamePhase::Setup)
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
		WaveEngine->WaveAccelerated.AddDynamic(this, &ARushGameMode::OnWaveAccelerated);
		WaveEngine->SequenceSpawnsDestroyed.AddDynamic(this, &ARushGameMode::Win);
	}
}

EGamePhase ARushGameMode::GetGamePhase() const
{
	return Phase;
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

bool ARushGameMode::IsNextWaveQueued()
{
	const int32 QueuedWaveIndex = WaveEngine->GetSequenceState().GetQueuedWave();
	return QueuedWaveIndex > -1 ? true : false;
}

ETsunamiWaveStartMethod ARushGameMode::GetNextWaveStartMethod()
{
	const int32 QueuedWaveIndex = WaveEngine->GetSequenceState().GetQueuedWave();
	return IsNextWaveQueued() ? WaveEngine->GetMountedSequence()->GetWave(QueuedWaveIndex)->StartMethod : ETsunamiWaveStartMethod::External;
}

float ARushGameMode::GetNextWaveStartTimeElapsedPercent()
{
	const int32 QueuedWaveIndex = WaveEngine->GetSequenceState().GetQueuedWave();
	if (IsNextWaveQueued())
	{
		FTimerHandle& StartTimer = WaveEngine->GetSequenceState().ActiveWaves[QueuedWaveIndex].StartTimer;
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		return TimerManager.GetTimerElapsed(StartTimer) / TimerManager.GetTimerRate(StartTimer);
	}

	return 0.f;
}

TMap<TSubclassOf<AActor>, int32> ARushGameMode::GetNextWaveStats()
{
	return UTsunamiBlueprintLibrary::GetWaveStats(WaveEngine->GetMountedSequence(), WaveEngine->GetSequenceState().GetQueuedWave());
}

void ARushGameMode::StartNextWave()
{
	if (Phase == EGamePhase::Setup)
	{
		Phase = EGamePhase::Spawning;
	}
	
	WaveEngine->ManuallyStartQueuedWave();
}

void ARushGameMode::OnWaveAccelerated(int32 Wave, float TotalTime, float ElapsedTime)
{
	AddGold(TotalTime - ElapsedTime);
}

void ARushGameMode::Win()
{
	Phase = EGamePhase::Complete;
}

void ARushGameMode::Lose()
{
	Phase = EGamePhase::Complete;
}
