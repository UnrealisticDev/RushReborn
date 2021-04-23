#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineRepeater.generated.h"

class USplineComponent;

UCLASS()
class ASplineRepeater : public AActor
{
	GENERATED_BODY()

public:

	ASplineRepeater();
	void OnConstruction(const FTransform& Transform) override;

	TArray<USplineComponent*> GetSplines() const;

protected:

	UPROPERTY()
	USplineComponent* RootSpline;

	UPROPERTY()
	USplineComponent* RightSpline;

	UPROPERTY()
	USplineComponent* LeftSpline;

	UPROPERTY(EditAnywhere, Category = Repeat)
	float LateralOffset;
};
