#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatantInterface.generated.h"

class AActor;

UINTERFACE(meta = (CannotImplementInterfaceInBlueprints))
class UCombatantInterface : public UInterface
{
	GENERATED_BODY()
};

class ICombatantInterface
{
	GENERATED_BODY()

public:

	DECLARE_DELEGATE(FAttackFinished);
	
	virtual bool IsAlive() const { return true; }

	virtual void Attack(AActor* Target) {}
	virtual void Attack(AActor* Target, FAttackFinished OnAttackFinished) {};
};