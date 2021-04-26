#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "BombardProjectile.generated.h"

class UCurveFloat;

UCLASS()
class ABombardProjectile : public AProjectile
{
	GENERATED_BODY()

public:

	ABombardProjectile();
	
	void Move(float DeltaSeconds) override;
	void Impact() override;

private:
	
	/** Calculates arc vertex. */
	FVector CalculateArcVertex() const;

	/** Apply damage to enemies in area. */
	void ApplyDamageInArea();

	/** Current movement lerp alpha. */
	UPROPERTY()
	float MoveAlpha;

	/** Area of effect to damage enemies in. */
	UPROPERTY(EditAnywhere, Category = Impact)
	float AreaOfEffect;
};
