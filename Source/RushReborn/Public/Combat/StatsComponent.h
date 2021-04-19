#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatsComponent.generated.h"

class AActor;
class UDamageType;
class AController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthDepleted);

UCLASS()
class UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UStatsComponent();
	void InitializeComponent() override;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(BlueprintAssignable)
	FHealthDepleted HealthDepleted;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Defensive")
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Stats | Defensive")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Defensive")
	int Armor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Defensive")
	int MagicResistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Offensive")
	FFloatRange AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Offensive")
	float AttackRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats | Movement")
	float MovementSpeed;
};
