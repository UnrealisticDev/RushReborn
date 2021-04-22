#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_WaitAnyEnemy.generated.h"

UCLASS()
class UBTTask_WaitAnyEnemy : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_WaitAnyEnemy();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UFUNCTION()
	void OnOwnerOverlapped(AActor* OwnerActor, AActor* OtherActor);

	void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

private:

	UPROPERTY()
	TWeakObjectPtr<UBehaviorTreeComponent> OwnerComponent;
};
