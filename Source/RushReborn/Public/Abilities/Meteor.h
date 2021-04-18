#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Meteor.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;

UCLASS(Config=Game)
class AMeteor : public AActor
{
	GENERATED_BODY()

public:

	AMeteor();

	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void ApplyDamageToActor(AActor* Actor);

private:

	UPROPERTY()
	USphereComponent* Collision;

	UPROPERTY()
	UParticleSystemComponent* BodyParticle;

	UPROPERTY()
	UProjectileMovementComponent* Movement;

	UPROPERTY(Config)
	float ImpactRadius;
	
	UPROPERTY()
	FFloatRange DamageOnImpact;

	UPROPERTY(Config)
	FSoftObjectPath ImpactParticle;
};
