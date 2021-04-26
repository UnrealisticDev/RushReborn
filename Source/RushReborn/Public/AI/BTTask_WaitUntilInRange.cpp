#include "BTTask_WaitUntilInRange.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_WaitUntilInRange::UBTTask_WaitUntilInRange()
{
	Range = 50.f;
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_WaitUntilInRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UBTTask_WaitUntilInRange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* SelfActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Self.SelectedKeyName));
	AActor* OtherActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Other.SelectedKeyName));

	if (!SelfActor || !OtherActor)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (FVector::Dist(SelfActor->GetActorLocation(), OtherActor->GetActorLocation()) <= Range)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
