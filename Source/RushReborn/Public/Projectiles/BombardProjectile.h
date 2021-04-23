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

	FVector CalculateArcVertex() const;
	
	void ApplyDamageInArea();

private:

	UPROPERTY()
	float MoveAlpha;

	UPROPERTY(EditAnywhere, Category = Impact)
	float AreaOfEffect;
};
