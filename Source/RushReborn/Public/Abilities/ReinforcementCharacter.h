#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatantInterface.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Character.h"
#include "ReinforcementCharacter.generated.h"

class UStatsComponent;

UCLASS(Blueprintable)
class AReinforcementCharacter : public ACharacter, public ITeamAgentInterface, public ICombatantInterface
{
	GENERATED_BODY()

public:

	AReinforcementCharacter();
	void BeginPlay() override;
	
	uint8 GetTeamId() override;

	bool IsEngaged() const override;
	AActor* GetActorEngagedWith() const override;
	void Engage(AActor* ActorToEngage) override;
	void Disengage() override;
	bool IsAlive() const override;

	UFUNCTION()
	void OnHealthDepleted();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStatsComponent* Stats;

private:

	UPROPERTY()
	AActor* ActorEngagedWith;
};
