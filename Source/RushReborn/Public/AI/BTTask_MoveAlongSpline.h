#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveAlongSpline.generated.h"

/**
 * Moves the owning actor along a spline.
 * Depends on the owning actor implementing
 * the ISplineFollowInterface.
 */
UCLASS()
class UBTTask_MoveAlongSpline : public UBTTaskNode
{
	GENERATED_BODY()

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
