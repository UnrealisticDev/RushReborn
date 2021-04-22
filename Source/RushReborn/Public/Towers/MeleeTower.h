#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "Components/ActorComponent.h"
#include "MeleeTower.generated.h"

UCLASS()
class USoldierDeathTracker : public UActorComponent
{
	GENERATED_BODY()

public:

	USoldierDeathTracker();
	
	void InitializeComponent() override;
	void UninitializeComponent() override;

	FSimpleDelegate Died;
};

UCLASS()
class AMeleeTower : public ATower
{
	GENERATED_BODY()

public:

	AMeleeTower();

	void BeginPlay() override;

	void SetStartingRallyPoint();

	FVector CalculateHomeLocation(int32 Index);
	
	void SpawnSoldier(int32 Index);

	void OnSoldierDied(int32 Index);

	void Destroyed() override;

protected:
	
	UPROPERTY(EditAnywhere, Category = Influence)
	float InfluenceRadius;

	UPROPERTY(EditAnywhere, Category = Soldier)
	TSubclassOf<AActor> SoldierClass;

	UPROPERTY()
	FVector RallyPoint;

	UPROPERTY(EditAnywhere, Category = Rally)
	float RallyOffset;

	TWeakObjectPtr<APawn> Soldiers[3];

	UPROPERTY()
	bool bManualDestroy;
};
