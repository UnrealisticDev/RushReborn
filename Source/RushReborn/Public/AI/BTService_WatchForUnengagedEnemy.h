#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_WatchForUnengagedEnemy.generated.h"

/**
 * Looks for unengaged enemies for the owner actor
 * to engage. This prevents multiple defenders
 * from tunnel-visioning onto a single enemy while
 * other enemies run by.
 */
UCLASS()
class UBTService_WatchForUnengagedEnemy : public UBTService
{
	GENERATED_BODY()

public:

	UBTService_WatchForUnengagedEnemy();
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:

	/**
	 * An unengaged enemy to target.
	 * Will be set when found, but untouched otherwise.
	 */
	UPROPERTY(EditAnywhere, Category = Search)
	FBlackboardKeySelector UnengagedEnemy;

	/** The distance from owner for searching for enemies. */
	UPROPERTY(EditAnywhere, Category = Search)
	float SearchRadius;

	/** The defender AI state. */
	UPROPERTY(EditAnywhere, Category = Search)
	FBlackboardKeySelector State;
};
