#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FinishRallying.generated.h"

UCLASS()
class UBTTask_FinishRallying : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_FinishRallying();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere, Category = Rallying)
	FBlackboardKeySelector bRallying;
};
