#include "SplineMovementComponent.h"
#include "Components/SplineComponent.h"

void USplineMovementComponent::SetSplineToFollow(USplineComponent* Spline)
{
	SplineToFollow = Spline;
}

void USplineMovementComponent::StartSplineMovement()
{
	check(SplineToFollow);
	SetMovementMode(EMovementMode::MOVE_Custom);
}

void USplineMovementComponent::StopSplineMovement()
{
	SetMovementMode(EMovementMode::MOVE_Walking);
}

void USplineMovementComponent::PhysCustom(float DeltaTime, int32 Iterations)
{
	DistanceOnSpline += MaxWalkSpeed * DeltaTime;

	const FTransform& OldTransform = UpdatedComponent->GetComponentTransform();
	FTransform NewTransform = SplineToFollow->GetTransformAtDistanceAlongSpline(DistanceOnSpline, ESplineCoordinateSpace::World);
	{
		FVector NewLocation = NewTransform.GetLocation();
		NewLocation += GetPawnCapsuleExtent(EShrinkCapsuleExtent::SHRINK_None);
		NewTransform.SetLocation(NewLocation);
	}
	UpdatedComponent->SetWorldTransform(NewTransform);

	Velocity = (NewTransform.GetLocation() - OldTransform.GetLocation()) * (1.f / DeltaTime);

	if (DistanceOnSpline >= SplineToFollow->GetDistanceAlongSplineAtSplinePoint(SplineToFollow->GetNumberOfSplinePoints() - 1))
	{
		StopSplineMovement();
	}
}
