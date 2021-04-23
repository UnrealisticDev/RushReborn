#include "BTTask_MoveAlongSpline.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Characters/SplineFollowInterface.h"

EBTNodeResult::Type UBTTask_MoveAlongSpline::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Cast<ISplineFollowInterface>(OwnerComp.GetAIOwner()->GetPawn())->StartSplineMovement();

	return EBTNodeResult::InProgress;
}

EBTNodeResult::Type UBTTask_MoveAlongSpline::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (OwnerComp.GetAIOwner() && OwnerComp.GetAIOwner()->GetPawn())
	{
		Cast<ISplineFollowInterface>(OwnerComp.GetAIOwner()->GetPawn())->StopSplineMovement();
	}
	
	return EBTNodeResult::Aborted;
}
