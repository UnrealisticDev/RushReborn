#include "BTTask_MoveAlongSpline.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Invaders/SplineFollowInterface.h"

EBTNodeResult::Type UBTTask_MoveAlongSpline::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Cast<ISplineFollowInterface>(OwnerComp.GetAIOwner()->GetPawn())->StartSplineMovement();

	return EBTNodeResult::InProgress;
}
