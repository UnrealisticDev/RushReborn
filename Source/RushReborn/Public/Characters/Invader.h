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

UCLASS(Blueprintable)
class AInvader : public ACharacter, public ITeamAgentInterface, public IEngageeInterface, public ICombatantInterface, public ISplineFollowInterface
{
	GENERATED_BODY()

public:

	AInvader(const FObjectInitializer& ObjectInitializer);
	void BeginPlay() override;

	uint8 GetTeamId() override;

	void EngagedBy(IEngagorInterface* Engagor) override;
	void DisengagedBy(IEngagorInterface* Engagor) override;
	bool IsEngaged() const override;
	int32 GetEngagementCount() const override;
	
	bool IsAlive() const override;
	void Attack(AActor* Target) override;

	UFUNCTION()
	void OnHealthDepleted();

	void SetSplineToFollow(USplineComponent* Spline) override;
	void StartSplineMovement() override;
	void StopSplineMovement() override;
	float GetRemainingDistanceAlongSpline() override;

protected:

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* Healthbar;
	
	UPROPERTY(VisibleAnywhere)
	UStatsComponent* Stats;

private:

	UPROPERTY()
	TArray<TScriptInterface<IEngagorInterface>> Engagors;
	
	UPROPERTY()
	FName IsEngagedKeyName;

	UPROPERTY()
	FName TargetKeyName;
};
