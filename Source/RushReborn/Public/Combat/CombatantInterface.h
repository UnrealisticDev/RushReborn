
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatantInterface.generated.h"

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
	virtual void SetEngaged(bool bNewEngaged) = 0;
	virtual bool IsAlive() const = 0;
	virtual void Attack(FAttackFinished OnAttackFinished) {};
};