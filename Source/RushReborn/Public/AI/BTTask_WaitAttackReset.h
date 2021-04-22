#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_WaitAttackReset.generated.h"

UCLASS(HideCategories=(Wait))
class UBTTask_WaitAttackReset : public UBTTask_Wait
{
	GENERATED_BODY()

public:

	UBTTask_WaitAttackReset();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
