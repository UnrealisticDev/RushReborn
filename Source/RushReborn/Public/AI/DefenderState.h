#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DefenderState.generated.h"

UENUM(BlueprintType)
enum class EDefenderState : uint8
{
	Idle,
	Rally,
	Engaged,
	Attacking
};

UCLASS()
class UBTTask_SetDefenderState : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_SetDefenderState();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	FString GetStaticDescription() const override;

protected:

	UPROPERTY(EditAnywhere, Category = State)
	FBlackboardKeySelector State;

	UPROPERTY(EditAnywhere, Category = State)
	EDefenderState NewState;
};
