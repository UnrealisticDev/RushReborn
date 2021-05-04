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
	BodyParticle->SetTemplate(ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("ParticleSystem'/Game/Marketplace/ParagonMinions/FX/Particles/PlayerBuffs/Proto_DroppedBuff_RedBuff.Proto_DroppedBuff_RedBuff'")).Object);
	BodyParticle->SetupAttachment(Collision);
	BodyParticle->SetRelativeScale3D(FVector(2.f));
	BodyParticle->SetRelativeRotation(FRotator(-90, 0, 0));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->MaxSpeed = 0;
	Movement->Velocity = FVector(0, 0, -2000.f);
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
		if (UTeamUtilities::AreEnemies(HitActor, GetInstigatorController()))
		{
			ApplyDamageToActor(HitActor);
		}
	}
	
	if (ImpactParticle.IsValid())
	{
		FTransform ImpactParticleTransform;
		ImpactParticleTransform = GetActorTransform();
		ImpactParticleTransform.SetScale3D(FVector(5.f));
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Cast<UParticleSystem>(ImpactParticle.TryLoad()), ImpactParticleTransform);
	}

	UGameplayStatics::PlaySoundAtLocation(this, Cast<USoundBase>(ImpactSound.TryLoad()), GetActorLocation(), 0.5f);

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
