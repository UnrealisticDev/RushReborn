#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SearchForEnemy.generated.h"

/**
 * Search for an enemy in the given radius,
 * prioritizing:
 * 1. Engagement status - Prefer unengaged enemies
 * 2. Proximity - Prefer closer enemies
 */
UCLASS()
class UBTService_SearchForEnemy : public UBTService
{
	GENERATED_BODY()

public:

	UBTService_SearchForEnemy();

protected:

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	/** The found enemy to target. */
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector FoundEnemy;

	/** The distance from owner actor to search for enemies. */
	UPROPERTY(EditAnywhere, Category = Search)
	float SearchRadius;
};
