#include "BTTask_FinishRallying.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FinishRallying::UBTTask_FinishRallying()
{
	NodeName = "Finish Rallying";
}

EBTNodeResult::Type UBTTask_FinishRallying::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsBool(bRallying.SelectedKeyName, false);
	return EBTNodeResult::Succeeded;
}
