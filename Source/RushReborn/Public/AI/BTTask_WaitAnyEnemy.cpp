#include "BTTask_WaitAnyEnemy.h"
#include "AIController.h"
#include "Combat/TeamUtilities.h"

UBTTask_WaitAnyEnemy::UBTTask_WaitAnyEnemy()
{
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_WaitAnyEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner() || !OwnerComp.GetAIOwner()->GetPawn())
	{
		return EBTNodeResult::Failed;
	}

	OwnerComp.GetAIOwner()->GetPawn()->OnActorBeginOverlap.AddDynamic(this, &UBTTask_WaitAnyEnemy::OnOwnerOverlapped);
	OwnerComponent = &OwnerComp;

	return EBTNodeResult::InProgress;
}

void UBTTask_WaitAnyEnemy::OnOwnerOverlapped(AActor* OwnerActor, AActor* OtherActor)
{
	if (UTeamUtilities::AreEnemies(OwnerActor, OtherActor))
	{
		FinishLatentTask(*OwnerComponent.Get(), EBTNodeResult::Succeeded);
	}
}

void UBTTask_WaitAnyEnemy::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	if (OwnerComp.GetAIOwner() && OwnerComp.GetAIOwner()->GetPawn())
	{
		OwnerComp.GetAIOwner()->GetPawn()->OnActorBeginOverlap.RemoveDynamic(this, &UBTTask_WaitAnyEnemy::OnOwnerOverlapped);
	}
}

