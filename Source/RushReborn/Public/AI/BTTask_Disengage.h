#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Disengage.generated.h"

/**
 * The owner actor will disengage any
 * currently engaged target.
 *
 * The owner actor must implement the
 * IEngagorInterface.
 */
UCLASS()
class UBTTask_Disengage : public UBTTaskNode
{
	GENERATED_BODY()

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
