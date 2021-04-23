#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WaitOverlapEnemy.generated.h"

UCLASS()
class UBTTask_WaitOverlapEnemy : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_WaitOverlapEnemy();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnOwnerOverlapped(AActor* OwnerActor, AActor* OtherActor);

	void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:

	UPROPERTY()
	TWeakObjectPtr<UBehaviorTreeComponent> OwnerComponent;
};
