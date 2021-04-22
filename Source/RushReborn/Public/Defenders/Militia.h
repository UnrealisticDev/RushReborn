#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatantInterface.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Character.h"
#include "Militia.generated.h"

class UStatsComponent;

UCLASS()
class AMilitia : public ACharacter, public ITeamAgentInterface, public ICombatantInterface
{
	GENERATED_BODY()

public:

	AMilitia();
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

	void Destroyed() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStatsComponent* Stats;

private:
	
	UPROPERTY()
	AActor* ActorEngagedWith;
};
