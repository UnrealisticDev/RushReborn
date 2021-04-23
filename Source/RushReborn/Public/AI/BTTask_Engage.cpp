#include "BTTask_Engage.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/CombatantInterface.h"

EBTNodeResult::Type UBTTask_Engage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));
	
	Cast<ICombatantInterface>(OwningPawn)->Engage(TargetActor);

	return EBTNodeResult::Succeeded;
}
