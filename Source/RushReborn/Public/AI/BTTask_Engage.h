#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Engage.generated.h"

/**
 * The owner actor will engage the target
 * actor.
 *
 * The owner actor must implement the IEngagorInterface,
 * and the target actor must implement the IEngageeInterface.
 */
UCLASS()
class UBTTask_Engage : public UBTTaskNode
{
	GENERATED_BODY()

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	/** The target to engage. */
	UPROPERTY(EditAnywhere, Category = Engage)
	FBlackboardKeySelector Target;
};
