#pragma once

#include "CoreMinimal.h"
#include "SplineFollowInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SplineMovementComponent.generated.h"

class USplineComponent;

/**
 * Custom character movement component
 * with the ability to follow splines.
 */
UCLASS()
class USplineMovementComponent : public UCharacterMovementComponent, public ISplineFollowInterface
{
	GENERATED_BODY()

public:

	/** Set the spline to follow (but does not start spline movement). */
	void SetSplineToFollow(USplineComponent* Spline) override;

	//~ Begin ISplineFollowInterface 
	void StartSplineMovement() override;
	void StopSplineMovement() override;
	float GetRemainingDistanceAlongSpline() override;
	//~ End ISplineFollowInterface

	/** Custom movement tick. */
	void PhysCustom(float DeltaTime, int32 Iterations) override;

private:

	/** The spline to follow. */
	UPROPERTY()
	USplineComponent* SplineToFollow;

	/** Current distance along spline. */
	UPROPERTY()
	float DistanceOnSpline;
};
