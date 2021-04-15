#pragma once

#include "CoreMinimal.h"
#include "Abilities/Ability.h"
#include "ReinforcementsAbility.generated.h"

UCLASS(Config=Game)
class UReinforcementsAbility : public UAbility
{
	GENERATED_BODY()

public:

	UReinforcementsAbility();

	void Activate(const FAbilityPayload& Payload) override;

private:

	UPROPERTY(Config)
	FSoftClassPath SpawnClass;

	UPROPERTY()
	FVector SpawnOffset;
};
