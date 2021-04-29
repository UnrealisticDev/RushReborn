#include "BTTask_WaitOverlapEnemy.h"
#include "AIController.h"
#include "Combat/TeamUtilities.h"

UBTTask_WaitOverlapEnemy::UBTTask_WaitOverlapEnemy()
{
	NodeName = "Wait Overlap Enemy";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_WaitOverlapEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner() || !OwnerComp.GetAIOwner()->GetPawn())
	{
		return EBTNodeResult::Failed;
	}

	AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
	TArray<AActor*> CurrentOverlaps;
	OwnerActor->GetOverlappingActors(CurrentOverlaps);
	if (CurrentOverlaps.Num() > 1 
		&& CurrentOverlaps.FindByPredicate
		(
			[OwnerActor](AActor* OverlappingActor){return UTeamUtilities::AreEnemies(OwnerActor, OverlappingActor);}
		))
	{
		return EBTNodeResult::Succeeded;
	}

	OwnerComp.GetAIOwner()->GetPawn()->OnActorBeginOverlap.AddUniqueDynamic(this, &UBTTask_WaitOverlapEnemy::OnOwnerOverlapped);
	OwnerComponent = &OwnerComp;

	return EBTNodeResult::InProgress;
}

void UBTTask_WaitOverlapEnemy::OnOwnerOverlapped(AActor* OwnerActor, AActor* OtherActor)
{
	if (UTeamUtilities::AreEnemies(OwnerActor, OtherActor))
	{
		FinishLatentTask(*OwnerComponent.Get(), EBTNodeResult::Succeeded);
	}
}

void UBTTask_WaitOverlapEnemy::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	if (OwnerComp.GetAIOwner() && OwnerComp.GetAIOwner()->GetPawn())
	{
		OwnerComp.GetAIOwner()->GetPawn()->OnActorBeginOverlap.RemoveDynamic(this, &UBTTask_WaitOverlapEnemy::OnOwnerOverlapped);
	}
}

