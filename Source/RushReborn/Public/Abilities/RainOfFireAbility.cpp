#include "RainOfFireAbility.h"
#include "Meteor.h"
#include "UObject/Object.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"

URainOfFireAbility::URainOfFireAbility()
	: ProjectileCount(3)
	, ProjectileSpawnRadius(200.f)
	, ProjectileSpawnHeight(2000.f)
	, ProjectileSpawnInterval(0.5f)
{
	Title = NSLOCTEXT("RainOfFire", "RainOfFire Title", "Rain of Fire");
	Description = NSLOCTEXT("RainOfFire", "RainOfFire Description", "Rains fire and brimstone from the sky.");
	Icon = ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("Texture2D'/Game/Marketplace/PiP_Survival/Textures/Survival/256x256/T_Drips_256x256.T_Drips_256x256'")).Object;
	Cooldown = 80.f;

	ProjectileClass = AMeteor::StaticClass();
}

bool URainOfFireAbility::CanActivate(const FAbilityPayload& Payload)
{
	FHitResult HitTargetingZone;
	GetWorld()->LineTraceSingleByChannel
	(
		HitTargetingZone, 
		Payload.Location + FVector(0, 0, 100.f), 
		Payload.Location + FVector(0, 0, -100.f),
		ECollisionChannel::ECC_GameTraceChannel1 /* Targeting */
	);

	return HitTargetingZone.IsValidBlockingHit();
}

void URainOfFireAbility::Activate(const FAbilityPayload& Payload)
{
	Super::Activate(Payload);

	TargetLocation = Payload.Location;
	ProjectilesSpawned = 0;

	const bool bShouldLoop = true;
	const float InitialDelay = 0.0f;
	GetWorld()->GetTimerManager().SetTimer
	(
		ProjectileSpawnTimer,
		this, &URainOfFireAbility::SpawnProjectile,
		ProjectileSpawnInterval,
		bShouldLoop,
		InitialDelay
	);
}

void URainOfFireAbility::SpawnProjectile()
{
	ProjectilesSpawned += 1;

	FTransform SpawnTransform;
	{
		FVector SpawnOffset;
		const float RandAngle = FMath::RandRange(0.f, 360.f);
		const float RandRadius = FMath::RandRange(0.f, ProjectileSpawnRadius);
		SpawnOffset.X = UKismetMathLibrary::DegSin(RandAngle) * RandRadius;
		SpawnOffset.Y = UKismetMathLibrary::DegCos(RandAngle) * RandRadius;
		SpawnOffset.Z = ProjectileSpawnHeight;

		SpawnTransform.SetLocation(TargetLocation + SpawnOffset);
	}

	AActor* Projectile = GetWorld()->SpawnActorAbsolute(ProjectileClass, SpawnTransform);
	Projectile->SetInstigator(UGameplayStatics::GetPlayerPawn(this, 0));

	if (ProjectilesSpawned >= ProjectileCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(ProjectileSpawnTimer);
	}
}
