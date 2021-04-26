#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * The owner actor attacks the given target.
 * The owner actor must implement the ICombatantInterface.
 *
 * Nulls out Target key if it is invalid.
 */
UCLASS()
class UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	/** The target actor to attack. */
	UPROPERTY(EditAnywhere, Category = Attack)
	FBlackboardKeySelector Target;
};
