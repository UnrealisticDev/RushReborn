#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_ValidateTarget.generated.h"

/**
 * Ensures that target is valid,
 * nulling it out if it is not.
 */
UCLASS()
class UBTService_ValidateTarget : public UBTService
{
	GENERATED_BODY()

protected:

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	/** The current target. */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Target;
};
