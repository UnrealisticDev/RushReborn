#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;

UCLASS(Blueprintable)
class AProjectile : public AActor
{
	GENERATED_BODY()

public:

	AProjectile();
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	void CacheStartLocation();
	
	void SetTarget(AActor* InTarget);
	void SetTarget(FVector InTarget);

	virtual void Move(float DeltaSeconds);

	void CacheTargetLocation();

	bool HasReachedTarget() const;

	virtual void Impact();

	void SpawnImpactParticle();

protected:

	UPROPERTY()
	FVector StartLocation;
	
	UPROPERTY()
	AActor* Target;
	
	UPROPERTY()
	FVector TargetLocation;

	UPROPERTY()
	float TargetThreshold;

	UPROPERTY(EditAnywhere, Category = Movement)
	float FlightSpeed;

	UPROPERTY(EditAnywhere, Category = Movement)
	float ArcHeight;

	UPROPERTY(EditAnywhere, Category = Impact)
	UParticleSystem* ImpactParticle;
};
