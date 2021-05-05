#include "BTService_ValidateTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/CombatantInterface.h"

void UBTService_ValidateTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UObject* TargetObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName);
	if (TargetObject == nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, nullptr);
	}

	ICombatantInterface* TargetCombatant = Cast<ICombatantInterface>(TargetObject);
	if (!TargetCombatant || !TargetCombatant->IsAlive())
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, nullptr);
	}
}
