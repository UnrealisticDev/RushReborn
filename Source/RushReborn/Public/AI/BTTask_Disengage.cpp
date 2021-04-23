#include "BTTask_Disengage.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/EngagementInterfaces.h"

EBTNodeResult::Type UBTTask_Disengage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IEngagorInterface* EngagorOwner = Cast<IEngagorInterface>(OwnerComp.GetAIOwner()->GetPawn());

	if (!EngagorOwner)
	{
		return EBTNodeResult::Failed;
	}
	
	EngagorOwner->Disengage();

	return EBTNodeResult::Succeeded;
}
