#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatantInterface.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Character.h"
#include "Defender.generated.h"

class UWidgetComponent;
class UStatsComponent;

UCLASS()
class ADefender : public ACharacter, public ITeamAgentInterface, public ICombatantInterface
{
	GENERATED_BODY()

public:

	ADefender();
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

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* Healthbar;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStatsComponent* Stats;

private:
	
	UPROPERTY()
	AActor* ActorEngagedWith;
};
