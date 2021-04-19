#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatantInterface.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Character.h"
#include "Invader.generated.h"

class UWidgetComponent;
class UStatsComponent;

UCLASS(Blueprintable)
class AInvader : public ACharacter, public ITeamAgentInterface, public ICombatantInterface
{
	GENERATED_BODY()

public:

	AInvader();
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

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* Healthbar;
	
	UPROPERTY(VisibleAnywhere)
	UStatsComponent* Stats;

private:

	UPROPERTY()
	AActor* ActorEngagedWith;
};
