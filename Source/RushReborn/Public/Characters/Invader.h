#pragma once

#include "CoreMinimal.h"
#include "SplineFollowInterface.h"
#include "Combat/CombatantInterface.h"
#include "Combat/EngagementInterfaces.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Character.h"
#include "Invader.generated.h"

class UWidgetComponent;
class UStatsComponent;

/**
 * An Invader is the base class for all
 * enemies of the player. Their primary behaviors include
 * moving along a spline and attacking targets when engaged.
 */
UCLASS(Blueprintable)
class AInvader : public ACharacter, public ITeamAgentInterface, public IEngageeInterface, public ICombatantInterface, public ISplineFollowInterface
{
	GENERATED_BODY()

public:

	AInvader(const FObjectInitializer& ObjectInitializer);
	void BeginPlay() override;

	//~ Begin ITeamAgentInterface
	uint8 GetTeamId() override;
	//~ End ITeamAgentInterface

	//~ Begin IEngageeInterface
	void EngagedBy(IEngagorInterface* Engagor) override;
	void DisengagedBy(IEngagorInterface* Engagor) override;
	bool IsEngaged() const override;
	int32 GetEngagementCount() const override;
	//~ End IEngageeInterface

	//~ Begin ICombatantInterface
	bool IsAlive() const override;
	void Attack(AActor* Target) override;
	//~ End ICombatantInterface

	UFUNCTION()
	void OnHealthDepleted();

	//~ Begin ISplineFollowInterface
	void SetSplineToFollow(USplineComponent* Spline) override;
	void StartSplineMovement() override;
	void StopSplineMovement() override;
	float GetRemainingDistanceAlongSpline() override;
	//~ End ISplineFollowInterface

	void Destroyed() override;

protected:

	/** Healthbar widget. */
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* Healthbar;

	/** Stats component. */
	UPROPERTY(VisibleAnywhere)
	UStatsComponent* Stats;

	/** Gold earned on death (even when invader reaches home base). */
	UPROPERTY(EditInstanceOnly, Category = Death)
	int32 Bounty;

private:

	/** List of current engagors. */
	UPROPERTY()
	TArray<TScriptInterface<IEngagorInterface>> Engagors;

	/** Blackboard key representing engagement flag. */
	UPROPERTY()
	FName IsEngagedKeyName;

	/** Blackboard key representing current target. */
	UPROPERTY()
	FName TargetKeyName;
};
