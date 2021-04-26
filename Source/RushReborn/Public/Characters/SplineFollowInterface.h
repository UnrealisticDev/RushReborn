#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SplineFollowInterface.generated.h"

class USplineComponent;

/**
 * Exposes functionality related to
 * moving along a spline.
 */
UINTERFACE()
class USplineFollowInterface: public UInterface
{
	GENERATED_BODY()
};

class ISplineFollowInterface
{
	GENERATED_BODY()

public:

	/** Set the spline to follow. Does not start spline movement. */
	virtual void SetSplineToFollow(USplineComponent* Spline) {}

	/** Start following the spline. */
	virtual void StartSplineMovement() {}

	/** Stop following the spline. */
	virtual void StopSplineMovement() {}

	/** Get the distance left to travel on the spline. */
	virtual float GetRemainingDistanceAlongSpline() { return -1.f; }
};
