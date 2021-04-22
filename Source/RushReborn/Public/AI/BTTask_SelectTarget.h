#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SelectTarget.generated.h"

UCLASS()
class UBTTask_SelectTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = Select)
	FBlackboardKeySelector Target;
};
