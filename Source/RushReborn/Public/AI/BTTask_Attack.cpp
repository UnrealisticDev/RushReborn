#include "BTTask_Attack.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/CombatantInterface.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner() || !OwnerComp.GetAIOwner()->GetPawn() || !OwnerComp.GetAIOwner()->GetPawn()->Implements<UCombatantInterface>())
	{
		return EBTNodeResult::Failed;
	}
	
	ICombatantInterface* Attacker = Cast<ICombatantInterface>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* AttackTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));
	if (!AttackTarget)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, nullptr);
		return EBTNodeResult::Failed;
	}

	Attacker->Attack(AttackTarget);

	return EBTNodeResult::Succeeded;
}
