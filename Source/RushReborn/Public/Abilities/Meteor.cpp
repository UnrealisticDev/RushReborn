#include "Meteor.h"
#include "UObject/ConstructorHelpers.h"
#include "Combat/DamageTypes.h"
#include "Combat/TeamUtilities.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AMeteor::AMeteor()
	: ImpactRadius(200.f)
	, DamageOnImpact(30, 60)
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetSphereRadius(5.f);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	
	SetRootComponent(Collision);

	BodyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BodyParticle"));
	BodyParticle->SetTemplate(ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Developer/P_MeteorBody.P_MeteorBody'")).Object);
	BodyParticle->SetupAttachment(Collision);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->ProjectileGravityScale = 2.f;
}

void AMeteor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByChannel
	(
		Hits, 
		GetActorLocation(), 
		GetActorLocation() + 1, 
		FQuat::Identity, 
		ECollisionChannel::ECC_Pawn, 
		FCollisionShape::MakeSphere(ImpactRadius)
	);

	for (const FHitResult& LocalHit : Hits)
	{
		AActor* HitActor = LocalHit.Actor.Get();
		if (UTeamUtilities::AreEnemies(HitActor, GetInstigator()))
		{
			ApplyDamageToActor(HitActor);
		}
	}
	
	if (ImpactParticle.IsValid())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<UParticleSystem>(ImpactParticle.TryLoad()), GetActorTransform());
	}

	// A necessary hack to allow the body particle to gracefully complete
	// instead of just disappearing on impact
	BodyParticle->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	SetLifeSpan(0.5f);
}

void AMeteor::ApplyDamageToActor(AActor* Actor)
{
	check(Actor);

	const float DamageToApply = FMath::RandRange(DamageOnImpact.GetLowerBoundValue(), DamageOnImpact.GetUpperBoundValue());
	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = UTrueDamage::StaticClass();
	Actor->TakeDamage(DamageToApply, DamageEvent, nullptr, this);
}
