#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Idle.generated.h"

/** Do nothing. */
UCLASS()
class UBTTask_Idle : public UBTTaskNode
{
	GENERATED_BODY()

public:
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
