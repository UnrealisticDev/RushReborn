#pragma once

#include "CoreMinimal.h"
#include "SplineFollowInterface.h"
#include "Combat/CombatantInterface.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Character.h"
#include "Invader.generated.h"

class UWidgetComponent;
class UStatsComponent;

UCLASS(Blueprintable)
class AInvader : public ACharacter, public ITeamAgentInterface, public ICombatantInterface, public ISplineFollowInterface
{
	GENERATED_BODY()

public:

	AInvader(const FObjectInitializer& ObjectInitializer);
	void BeginPlay() override;

	uint8 GetTeamId() override;

	bool IsEngaged() const override;
	AActor* GetActorEngagedWith() const override;
	void Engage(AActor* ActorToEngage) override;
	void Disengage() override;
	bool IsAlive() const override;
	void Attack(AActor* Target) override;

	UFUNCTION()
	void OnHealthDepleted();

	void SetSplineToFollow(USplineComponent* Spline) override;
	void StartSplineMovement() override;
	void StopSplineMovement() override;

protected:

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* Healthbar;
	
	UPROPERTY(VisibleAnywhere)
	UStatsComponent* Stats;

private:

	UPROPERTY()
	AActor* ActorEngagedWith;

	UPROPERTY()
	FName IsEngagedKeyName;

	UPROPERTY()
	FName ActorEngagedWithKeyName;
};
