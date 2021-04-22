#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "MageProjectile.generated.h"

class UParticleSystem;

UCLASS()
class AMageProjectile : public AProjectile
{
	GENERATED_BODY()

public:

	AMageProjectile();
	
	void Move(float DeltaSeconds);
	void Impact() override;
	
	void ApplyDamageToTarget();
};
