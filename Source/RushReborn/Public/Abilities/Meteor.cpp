#include "Meteor.h"
#include "Combat/DamageTypes.h"
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
		ApplyDamageToActor(LocalHit.Actor.Get());
	}

	if (ImpactParticle.IsValid())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<UParticleSystem>(ImpactParticle.TryLoad()), GetActorTransform());
	}

	Destroy();
}

void AMeteor::ApplyDamageToActor(AActor* Actor)
{
	check(Actor);

	const float DamageToApply = FMath::RandRange(DamageOnImpact.GetLowerBoundValue(), DamageOnImpact.GetUpperBoundValue());
	FDamageEvent DamageEvent;
	DamageEvent.DamageTypeClass = UTrueDamage::StaticClass();
	Actor->TakeDamage(DamageToApply, DamageEvent, nullptr, this);
}
