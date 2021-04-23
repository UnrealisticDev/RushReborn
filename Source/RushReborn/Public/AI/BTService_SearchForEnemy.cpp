#include "BTService_SearchForEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/EngagementInterfaces.h"
#include "Combat/TeamUtilities.h"

UBTService_SearchForEnemy::UBTService_SearchForEnemy()
	: SearchRadius(100.f)
{
	
}

void UBTService_SearchForEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();
	const FVector OwnerLocation = OwnerPawn->GetActorLocation();
	
	TArray<FHitResult> Hits;	
	GetWorld()->SweepMultiByChannel
	(
		Hits, 
		OwnerLocation, 
		OwnerLocation + 1, 
		FQuat::Identity, 
		ECollisionChannel::ECC_Pawn, 
		FCollisionShape::MakeSphere(SearchRadius)
	);

	Hits.RemoveAll([&OwnerPawn](const FHitResult& Hit)
	{
		return !UTeamUtilities::AreEnemies(OwnerPawn, Hit.GetActor());
	});

	Hits.Sort([&OwnerLocation](const FHitResult& A, const FHitResult& B)
	{
		return FVector::Dist(A.GetActor()->GetActorLocation(), OwnerLocation) < FVector::Dist(B.GetActor()->GetActorLocation(), OwnerLocation);
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
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FoundEnemy.SelectedKeyName, Hit->GetActor());	
		}

		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FoundEnemy.SelectedKeyName, Hits[0].GetActor());	
		}
	}
}
