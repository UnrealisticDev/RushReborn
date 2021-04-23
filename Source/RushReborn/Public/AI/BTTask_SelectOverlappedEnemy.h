#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SelectOverlappedEnemy.generated.h"

UCLASS()
class UBTTask_SelectOverlappedEnemy : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_SelectOverlappedEnemy();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere, Category = Select)
	FBlackboardKeySelector SelectedEnemy;
};
