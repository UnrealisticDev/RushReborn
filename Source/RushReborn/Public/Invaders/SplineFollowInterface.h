#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SplineFollowInterface.generated.h"

class USplineComponent;

UINTERFACE()
class USplineFollowInterface: public UInterface
{
	GENERATED_BODY()
};

class ISplineFollowInterface
{
	GENERATED_BODY()

public:

	virtual void SetSplineToFollow(USplineComponent* Spline) {}
	virtual void StartSplineMovement() {}
	virtual void StopSplineMovement() {}
	virtual float GetRemainingDistanceAlongSpline() { return -1.f; }
};
