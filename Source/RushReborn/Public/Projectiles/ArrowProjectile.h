#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ArrowProjectile.generated.h"

class UCurveFloat;

/** Projectile used by archer tower. */
UCLASS()
class AArrowProjectile : public AProjectile
{
	GENERATED_BODY()

public:

	AArrowProjectile();
	
	void Move(float DeltaSeconds) override;
	void Impact() override;

private:
	
	/** Calculates arc vertex. */
	FVector CalculateArcVertex() const;

	/** Apply damage to target. */
	void ApplyDamageToTarget();

	/** Current movement lerp alpha. */
	UPROPERTY()
	float MoveAlpha;
};
