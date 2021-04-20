#include "BTTask_InitiateEngagement.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/CombatantInterface.h"

EBTNodeResult::Type UBTTask_InitiateEngagement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
	AActor* EnemyActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Enemy.SelectedKeyName));
	
	Cast<ICombatantInterface>(OwningPawn)->Engage(EnemyActor);

	return EBTNodeResult::Succeeded;
}
