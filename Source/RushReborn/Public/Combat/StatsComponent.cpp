#include "StatsComponent.h"
#include "DamageTypes.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/DamageType.h"
#include "Math/UnrealMathUtility.h"

UStatsComponent::UStatsComponent()
	: MaxHealth(1000)
	, Armor(50)
	, MagicResistance(50)
	, AttackDamage(40, 50)
	, AttackRate(1)
	, MovementSpeed(300)
{
	bWantsInitializeComponent = true;
}

void UStatsComponent::InitializeComponent()
{
	Super::InitializeComponent();

	CurrentHealth = MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UStatsComponent::OnTakeAnyDamage);
}

void UStatsComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                      AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageType->GetClass() == UPhysicalDamage::StaticClass())
	{
		Damage *= (100 - Armor) / 100.f;
	}

	else if (DamageType->GetClass() == UMagicalDamage::StaticClass())
	{
		Damage *= (100 - MagicResistance) / 100.f;
	}

	// else assume TrueDamage

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);

	if (!CurrentHealth)
	{
		HealthDepleted.Broadcast();
	}
}
