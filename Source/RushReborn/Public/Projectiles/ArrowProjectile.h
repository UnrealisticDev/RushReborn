#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ArrowProjectile.generated.h"

class UCurveFloat;

UCLASS()
class AArrowProjectile : public AProjectile
{
	GENERATED_BODY()

public:

	AArrowProjectile();
	
	void Move(float DeltaSeconds) override;
	void Impact() override;

	FVector CalculateArcVertex() const;
	
	void ApplyDamageToTarget();

private:

	UPROPERTY()
	float MoveAlpha;
};
