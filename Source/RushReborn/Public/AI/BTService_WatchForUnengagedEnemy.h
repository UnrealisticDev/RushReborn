#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_WatchForUnengagedEnemy.generated.h"

UCLASS()
class UBTService_WatchForUnengagedEnemy : public UBTService
{
	GENERATED_BODY()

public:

	UBTService_WatchForUnengagedEnemy();
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	UPROPERTY(EditAnywhere, Category = Search)
	FBlackboardKeySelector UnengagedEnemy;
	
	UPROPERTY(EditAnywhere, Category = Search)
	float SearchRadius;

	UPROPERTY(EditAnywhere, Category = Search)
	FBlackboardKeySelector State;
};
