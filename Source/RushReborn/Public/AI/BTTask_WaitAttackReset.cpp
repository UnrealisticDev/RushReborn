#include "BTTask_WaitAttackReset.h"
#include "AIController.h"
#include "Combat/StatsComponent.h"

UBTTask_WaitAttackReset::UBTTask_WaitAttackReset()
{
	NodeName = "Wait Attack Reset";
}

EBTNodeResult::Type UBTTask_WaitAttackReset::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
	if (OwnerActor)
	{
		UStatsComponent* OwnerStats = OwnerActor->FindComponentByClass<UStatsComponent>();
		if (OwnerStats)
		{
			WaitTime = OwnerStats->AttackRate;
		}
	}
		
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
