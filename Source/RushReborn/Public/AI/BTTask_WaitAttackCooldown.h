#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_WaitAttackCooldown.generated.h"

UCLASS(HideCategories=(Wait))
class UBTTask_WaitAttackCooldown : public UBTTask_Wait
{
	GENERATED_BODY()

public:

	UBTTask_WaitAttackCooldown();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	FString GetStaticDescription() const override;
};
