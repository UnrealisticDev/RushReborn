#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Meteor.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UParticleSystemComponent;

/**
 * The Meteor is spawned by the
 * Rain of Fire ability. It drops from the sky
 * and causes area of effect damage to enemies
 * on impact with any object of collision type "WorldStatic"
 * (in this case, the floor).
 */
UCLASS(Config=Game)
class AMeteor : public AActor
{
	GENERATED_BODY()

public:

	AMeteor();

	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

private:

	/** Utility function for applying damage to an actor. */
	void ApplyDamageToActor(AActor* Actor);

	/** The collision sphere, used for detecting impact. */
	UPROPERTY()
	USphereComponent* Collision;

	/** The particle representing the body of the meteor. */
	UPROPERTY()
	UParticleSystemComponent* BodyParticle;

	/**
	 * The projectile movement of the meteor.
	 * Does little more than apply gravity.
	 */
	UPROPERTY()
	UProjectileMovementComponent* Movement;

	/** The area of effect. */
	UPROPERTY(Config)
	float ImpactRadius;

	/** The amount of damage to apply on impact. */
	UPROPERTY()
	FFloatRange DamageOnImpact;

	/** The particle to spawn on impact. */
	UPROPERTY(Config)
	FSoftObjectPath ImpactParticle;
};
