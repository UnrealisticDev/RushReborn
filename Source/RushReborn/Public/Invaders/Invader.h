#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatantInterface.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Character.h"
#include "Invader.generated.h"

class UStatsComponent;

UCLASS(Blueprintable)
class AInvader : public ACharacter, public ITeamAgentInterface, public ICombatantInterface
{
	GENERATED_BODY()

public:

	AInvader();

	uint8 GetTeamId() override;

	bool IsEngaged() const override;
	void SetEngaged(bool bNewEngaged) override;
	bool IsAlive() const override;

	UFUNCTION()
	void OnHealthDepleted();

protected:

	UPROPERTY(VisibleAnywhere)
	UStatsComponent* Stats;

private:

	UPROPERTY()
	bool bIsEngaged;
};
