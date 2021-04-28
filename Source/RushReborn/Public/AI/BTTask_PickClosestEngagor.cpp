#include "BTTask_PickClosestEngagor.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/EngagementInterfaces.h"

UBTTask_PickClosestEngagor::UBTTask_PickClosestEngagor()
{
	NodeName = "Pick Closest Engagor";
}

EBTNodeResult::Type UBTTask_PickClosestEngagor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* OwnerActor = OwnerComp.GetAIOwner()->GetPawn();
	IEngageeInterface* EngageeOwner = Cast<IEngageeInterface>(OwnerActor);

	if (!EngageeOwner)
	{
		return EBTNodeResult::Failed;
	}

	if (EngageeOwner->GetEngagementCount() == 0)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, nullptr);
		return EBTNodeResult::Failed;
	}
	
	TArray<IEngagorInterface*> Engagors = EngageeOwner->GetEngagors();
	AActor* ClosestEngagor = Cast<AActor>(Engagors[0]);

	const FVector OwnerLocation = OwnerActor->GetActorLocation();
	for (IEngagorInterface* Engagor : Engagors)
	{
		if
		(
			FVector::Dist(OwnerLocation, ClosestEngagor->GetActorLocation())
			< FVector::Dist(OwnerLocation, Cast<AActor>(Engagor)->GetActorLocation())
		)
		{
			ClosestEngagor = Cast<AActor>(Engagor);
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, ClosestEngagor);

	return EBTNodeResult::Succeeded;
}
