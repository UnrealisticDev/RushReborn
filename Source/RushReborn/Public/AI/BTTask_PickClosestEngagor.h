#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PickClosestEngagor.generated.h"

/**
 * Pick the closest engagor to target.
 * The owner actor must implement the IEngageeInterface.
 *
 * Nulls out Target key if there are no Engagors.
 */
UCLASS()
class UBTTask_PickClosestEngagor : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_PickClosestEngagor();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	/** The closest engagor. */
	UPROPERTY(EditAnywhere, Category = Attack)
	FBlackboardKeySelector Target;
};
