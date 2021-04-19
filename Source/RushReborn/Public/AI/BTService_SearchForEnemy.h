#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SearchForEnemy.generated.h"

UCLASS()
class UBTService_SearchForEnemy : public UBTService
{
	GENERATED_BODY()

public:

	UBTService_SearchForEnemy();

protected:

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector FoundEnemy;
	
	UPROPERTY(EditAnywhere, Category = Search)
	float SearchRadius;
};
