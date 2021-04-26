#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_WaitAttackCooldown.generated.h"

/**
 * Wait for the duration of the owning
 * actor's attack rate. Depends on the owning actor
 * having a Stats component.
 */
UCLASS(HideCategories=(Wait))
class UBTTask_WaitAttackCooldown : public UBTTask_Wait
{
	GENERATED_BODY()

public:

	UBTTask_WaitAttackCooldown();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	FString GetStaticDescription() const override;
};
