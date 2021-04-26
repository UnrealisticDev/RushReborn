#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineRepeater.generated.h"

class USplineComponent;

/**
 * The spline repeater is a utility actor
 * that repeats a single root spline
 * on both sides of itself. This allows one to author
 * a single spline and get multiple matching paths.
 */
UCLASS()
class ASplineRepeater : public AActor
{
	GENERATED_BODY()

public:

	ASplineRepeater();
	void OnConstruction(const FTransform& Transform) override;

	/** Get a list of splines owned by this repeater. */
	TArray<USplineComponent*> GetSplines() const;

protected:

	/** The root spline that others follow. */
	UPROPERTY()
	USplineComponent* RootSpline;

	/** Spline to the left of root. */
	UPROPERTY()
	USplineComponent* RightSpline;

	/** Spline to the right of root. */
	UPROPERTY()
	USplineComponent* LeftSpline;

	/** The distance to offset Left and Right from root. */
	UPROPERTY(EditAnywhere, Category = Repeat)
	float LateralOffset;
};
