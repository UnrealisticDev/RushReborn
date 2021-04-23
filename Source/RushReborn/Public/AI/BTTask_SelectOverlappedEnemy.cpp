#include "BTTask_SelectOverlappedEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/TeamUtilities.h"
#include "Characters/SplineFollowInterface.h"

UBTTask_SelectOverlappedEnemy::UBTTask_SelectOverlappedEnemy()
{
	NodeName = "Select Overlapped Enemy";
}

EBTNodeResult::Type UBTTask_SelectOverlappedEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.GetAIOwner() || !OwnerComp.GetAIOwner()->GetPawn())
	{
		return EBTNodeResult::Failed;
	}

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	
	TArray<AActor*> OverlappingActors;
	OwnerPawn->GetOverlappingActors(OverlappingActors);
	OverlappingActors.RemoveAll([OwnerPawn](AActor* OverlappingActor)
		{
			return !UTeamUtilities::AreEnemies(OwnerPawn, OverlappingActor);
		});

	if (OverlappingActors.Num() > 0)
	{
		AActor* TargetClosestToBase = nullptr;

		for (AActor* Actor : OverlappingActors)
		{
			if (Actor->Implements<USplineFollowInterface>())
			{
				if (TargetClosestToBase == nullptr)
				{
					TargetClosestToBase = Actor;
				}

				else
				{
					if (Cast<ISplineFollowInterface>(Actor)->GetRemainingDistanceAlongSpline() < Cast<ISplineFollowInterface>(TargetClosestToBase)->GetRemainingDistanceAlongSpline())
					{
						TargetClosestToBase = Actor;
					}
				}
			}
		}
		
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(SelectedEnemy.SelectedKeyName, TargetClosestToBase);
	}

	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(SelectedEnemy.SelectedKeyName, nullptr);
	}

	return EBTNodeResult::Succeeded;
}

