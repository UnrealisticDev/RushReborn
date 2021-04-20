#pragma once

#include "CoreMinimal.h"
#include "SplineFollowInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SplineMovementComponent.generated.h"

class USplineComponent;

UCLASS()
class USplineMovementComponent : public UCharacterMovementComponent, public ISplineFollowInterface
{
	GENERATED_BODY()

public:

	void SetSplineToFollow(USplineComponent* Spline) override;
	void StartSplineMovement() override;
	void StopSplineMovement() override;
	
	void PhysCustom(float DeltaTime, int32 Iterations) override;

private:

	UPROPERTY()
	USplineComponent* SplineToFollow;

	UPROPERTY()
	float DistanceOnSpline;
};
