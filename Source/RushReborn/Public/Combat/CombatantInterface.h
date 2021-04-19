
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

	virtual bool IsEngaged() const = 0;
	virtual AActor* GetActorEngagedWith() const { return nullptr; }
	virtual void Engage(AActor* ActorToEngage) {}
	virtual void Disengage() {}

	virtual bool IsAlive() const = 0;

	virtual void Attack(AActor* Target) {}
	virtual void Attack(AActor* Target, FAttackFinished OnAttackFinished) {};
};