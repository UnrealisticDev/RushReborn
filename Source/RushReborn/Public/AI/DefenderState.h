#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DefenderState.generated.h"

/** The AI state of a defender. */
UENUM(BlueprintType)
enum class EDefenderState : uint8
{
	Idle,
	Rally,
	Engaged,
	Attacking
};

/** Set the defender AI state to the specified one. */
UCLASS()
class UBTTask_SetDefenderState : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_SetDefenderState();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	FString GetStaticDescription() const override;

protected:

	/** The state key to update. */
	UPROPERTY(EditAnywhere, Category = State)
	FBlackboardKeySelector State;

	/** The new state. */
	UPROPERTY(EditAnywhere, Category = State)
	EDefenderState NewState;
};
