#include "BTTask_WaitAttackCooldown.h"
#include "AIController.h"
#include "Combat/StatsComponent.h"

UBTTask_WaitAttackCooldown::UBTTask_WaitAttackCooldown()
{
	NodeName = "Wait Attack Cooldown";
}

EBTNodeResult::Type UBTTask_WaitAttackCooldown::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

FString UBTTask_WaitAttackCooldown::GetStaticDescription() const
{
	return "Wait Attack Cooldown";
}
