#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WaitOverlapEnemy.generated.h"

/**
 * Wait until the owner actor overlaps with an
 * enemy. Naturally, requires the owner actor to
 * have overlapping collision enabled.
 *
 * Task is instanced.
 */
UCLASS()
class UBTTask_WaitOverlapEnemy : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_WaitOverlapEnemy();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	/** Callback for when owner actor is overlapped. */
	UFUNCTION()
	void OnOwnerOverlapped(AActor* OwnerActor, AActor* OtherActor);

	void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:

	/**
	 * The owning behavior tree.
	 * Cached to allow finishing task from latent callback.
	 */
	UPROPERTY()
	TWeakObjectPtr<UBehaviorTreeComponent> OwnerComponent;
};
