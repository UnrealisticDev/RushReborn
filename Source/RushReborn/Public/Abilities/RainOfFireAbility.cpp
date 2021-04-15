#include "RainOfFireAbility.h"
#include "UObject/Object.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"

URainOfFireAbility::URainOfFireAbility()
	: ProjectileCount(3)
	, ProjectileSpawnRadius(100.f)
	, ProjectileSpawnHeight(1000.f)
	, ProjectileSpawnInterval(.1f)
{
	Title = NSLOCTEXT("RainOfFire", "RainOfFire Title", "Rain of Fire");
	Description = NSLOCTEXT("RainOfFire", "RainOfFire Description", "Rains fire and brimstone from the sky.");
	Icon = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Game/RushReborn/Art/UI/T_Asteroid.T_Asteroid'")).Object;
	Cooldown = 80.f;
}

void URainOfFireAbility::Activate(const FAbilityPayload& Payload)
{
	Super::Activate(Payload);

	check(ProjectileClass.IsValid());

	TargetLocation = Payload.Location;
	ProjectilesSpawned = 0;

	bool bShouldLoop = true;
	float bInitialDelay = 0.001f;
	GetWorld()->GetTimerManager().SetTimer
	(
		ProjectileSpawnTimer,
		this, &URainOfFireAbility::SpawnProjectile,
		ProjectileSpawnInterval,
		bShouldLoop,
		bInitialDelay
	);
}

void URainOfFireAbility::SpawnProjectile()
{
	ProjectilesSpawned += 1;

	FTransform SpawnTransform;
	{
		FVector SpawnOffset;
		float RandAngle = FMath::RandRange(0.f, 360.f);
		float RandRadius = FMath::RandRange(0.f, ProjectileSpawnRadius);
		SpawnOffset.X = UKismetMathLibrary::DegSin(RandAngle) * RandRadius;
		SpawnOffset.Y = UKismetMathLibrary::DegCos(RandAngle) * RandRadius;
		SpawnOffset.Z = ProjectileSpawnHeight;

		SpawnTransform.SetLocation(TargetLocation + SpawnOffset);
	}

	GetWorld()->SpawnActorAbsolute(ProjectileClass.TryLoadClass<UObject>(), SpawnTransform);

	if (ProjectilesSpawned >= ProjectileCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(ProjectileSpawnTimer);
	}
}
