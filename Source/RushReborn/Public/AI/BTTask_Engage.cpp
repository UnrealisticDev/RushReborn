#include "BTTask_Engage.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/EngagementInterfaces.h"

EBTNodeResult::Type UBTTask_Engage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IEngagorInterface* EngagorOwner = Cast<IEngagorInterface>(OwnerComp.GetAIOwner()->GetPawn());
	IEngageeInterface* EngageeTarget = Cast<IEngageeInterface>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));

	if (!EngagorOwner || !EngageeTarget)
	{
		return EBTNodeResult::Failed;
	}
	
	EngagorOwner->Engage(EngageeTarget);

	return EBTNodeResult::Succeeded;
}
