#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

struct FBTAttackTaskMemory
{
	FTimerHandle AttackTimer;
};

UCLASS()
class UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_Attack();
	uint16 GetInstanceMemorySize() const override;
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void Attack(UBehaviorTreeComponent* OwnerComp, AActor* Attacker, AActor* AttackTarget);

	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

	UPROPERTY(EditAnywhere, Category = Attack)
	FBlackboardKeySelector Target;
};
