#include "DefenderState.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetDefenderState::UBTTask_SetDefenderState()
{
	NodeName = "Set Militia State";
}

EBTNodeResult::Type UBTTask_SetDefenderState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(State.SelectedKeyName, (uint8)NewState);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_SetDefenderState::GetStaticDescription() const
{
	return FString::Printf(TEXT("Set state to %hhd."), NewState);
}
