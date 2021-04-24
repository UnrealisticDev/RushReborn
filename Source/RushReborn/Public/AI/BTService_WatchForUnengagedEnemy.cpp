#include "BTService_WatchForUnengagedEnemy.h"
#include "AIController.h"
#include "DefenderState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/EngagementInterfaces.h"
#include "Combat/TeamUtilities.h"

UBTService_WatchForUnengagedEnemy::UBTService_WatchForUnengagedEnemy()
{
	NodeName = "Watch for Unengaged Enemy";
}

void UBTService_WatchForUnengagedEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	const FVector OwnerLocation = OwnerPawn->GetActorLocation();

	IEngagorInterface* EngagorPawn = Cast<IEngagorInterface>(OwnerComp.GetAIOwner()->GetPawn());
	IEngageeInterface* CurrentEngagee = EngagorPawn->GetEngagee();
	if (CurrentEngagee && CurrentEngagee->GetEngagementCount() > 1)
	{
		TArray<FHitResult> Hits;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Cast<AActor>(CurrentEngagee));
		GetWorld()->SweepMultiByChannel
		(
			Hits,
			OwnerLocation,
			OwnerLocation + 1,
			FQuat::Identity,
			ECollisionChannel::ECC_Pawn,
			FCollisionShape::MakeSphere(SearchRadius),
			Params
		);

		Hits.RemoveAll([&OwnerPawn](const FHitResult& Hit)
		{
			return !UTeamUtilities::AreEnemies(OwnerPawn, Hit.GetActor());
		});

		Hits.Sort([&OwnerLocation](const FHitResult& A, const FHitResult& B)
		{
			return FVector::Dist(A.GetActor()->GetActorLocation(), OwnerLocation) < FVector::Dist(
				B.GetActor()->GetActorLocation(), OwnerLocation);
		});

		if (Hits.Num() > 0)
		{
			FHitResult* Hit = Hits.FindByPredicate([](const FHitResult& Hit)
			{
				IEngageeInterface* Engagee = Cast<IEngageeInterface>(Hit.GetActor());
				return Engagee && !Engagee->IsEngaged();
			});

			if (Hit)
			{
				EngagorPawn->Disengage();
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(UnengagedEnemy.SelectedKeyName, Hit->GetActor());
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(State.SelectedKeyName, (uint8)EDefenderState::Engaged);
			}
		}
	}
}
