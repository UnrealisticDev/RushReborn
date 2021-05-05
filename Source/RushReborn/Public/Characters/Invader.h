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
class UAnimMontage;
class UAnimSequence;
class USoundBase;

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
	TArray<IEngagorInterface*> GetEngagors() const override;
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

	void Die();
	void Destroyed() override;

protected:

	/** Apply damage to the target. */
	void ApplyDamageToTarget(AActor* Target);
	
	/** Healthbar widget. */
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* Healthbar;

	/** Stats component. */
	UPROPERTY(VisibleAnywhere)
	UStatsComponent* Stats;

	/** Delay before attack damage occurs. */
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	float AttackDelay;

	/** Attack montages to be played at random. */
	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TArray<UAnimMontage*> AttackMontages;

	/** Gold earned on death (even when invader reaches home base). */
	UPROPERTY(EditDefaultsOnly, Category = Death)
	int32 Bounty;

	/** Animation to play on death. */
	UPROPERTY(EditDefaultsOnly, Category = Death)
	UAnimSequence* DeathAnimation;

	/** Sound to play on death. */
	UPROPERTY(EditDefaultsOnly, Category = Death)
	USoundBase* DeathSound;

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

	/** Flag to keep track of death. */
	UPROPERTY()
	bool bDead;
};
