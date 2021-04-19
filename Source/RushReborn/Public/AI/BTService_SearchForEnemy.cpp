#include "BTService_SearchForEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/CombatantInterface.h"
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

	for (const FHitResult& Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if (UTeamUtilities::AreEnemies(OwnerPawn, Hit.GetActor()) && !Cast<ICombatantInterface>(HitActor)->IsEngaged())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FoundEnemy.SelectedKeyName, Hit.GetActor());
			break;
		}
	}
}
