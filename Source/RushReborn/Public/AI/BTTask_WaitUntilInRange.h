#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WaitUntilInRange.generated.h"

/**
 * Waits until the other actor is within
 * a specified range.
 */
UCLASS()
class UBTTask_WaitUntilInRange : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_WaitUntilInRange();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	/** Owning actor. */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Self;

	/** Other actor. */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Other;

	/** Range to wait on. */
	UPROPERTY(EditAnywhere, Category = Range)
	float Range;
};
