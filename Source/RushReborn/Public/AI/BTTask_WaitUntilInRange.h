#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WaitUntilInRange.generated.h"

UCLASS()
class UBTTask_WaitUntilInRange : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_WaitUntilInRange();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Self;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Other;

	UPROPERTY(EditAnywhere, Category = Range)
	float Range;
};
