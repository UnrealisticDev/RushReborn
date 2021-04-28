#include "BTService_ValidateTarget.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_ValidateTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName) == nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, nullptr);
	}
}
