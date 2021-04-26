#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SelectOverlappedEnemy.generated.h"

/**
 * Select an overlapped enemy for targeting,
 * prioritizing enemy distance from home base.
 *
 * If no overlapping enemies, sets SelectedEnemy
 * to nullptr.
 */
UCLASS()
class UBTTask_SelectOverlappedEnemy : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_SelectOverlappedEnemy();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	/** The selected enemy. */
	UPROPERTY(EditAnywhere, Category = Select)
	FBlackboardKeySelector SelectedEnemy;
};
