#include "SplineRepeater.h"
#include "Components/SplineComponent.h"

ASplineRepeater::ASplineRepeater()
	: LateralOffset(50.f)
{
	RootSpline = CreateDefaultSubobject<USplineComponent>(TEXT("RootSpline"));
	SetRootComponent(RootSpline);

	RightSpline = CreateDefaultSubobject<USplineComponent>(TEXT("RightSpline"));
	RightSpline->SetupAttachment(RootSpline);
	RightSpline->ClearSplinePoints();

	LeftSpline = CreateDefaultSubobject<USplineComponent>(TEXT("LeftSpline"));
	LeftSpline->SetupAttachment(RootSpline);
	LeftSpline->ClearSplinePoints();
}

void ASplineRepeater::OnConstruction(const FTransform& Transform)
{
	RightSpline->ClearSplinePoints();
	LeftSpline->ClearSplinePoints();
	
	ESplineCoordinateSpace::Type CoordinateSpace = ESplineCoordinateSpace::Local;
	for (int i = 0; i < RootSpline->GetNumberOfSplinePoints(); ++i)
	{
		FVector RootLocation = RootSpline->GetLocationAtSplinePoint(i, CoordinateSpace);
		FVector RootRightVector = RootSpline->GetRightVectorAtSplinePoint(i, CoordinateSpace);
		FVector RootTangent = RootSpline->GetTangentAtSplinePoint(i, CoordinateSpace);
		
		RightSpline->AddSplinePoint(RootLocation + (RootRightVector * LateralOffset), CoordinateSpace);
		RightSpline->SetTangentAtSplinePoint(i, RootTangent, CoordinateSpace);
		
		LeftSpline->AddSplinePoint(RootLocation + (RootRightVector * LateralOffset * -1), CoordinateSpace);
		LeftSpline->SetTangentAtSplinePoint(i, RootTangent, CoordinateSpace);
	}

	RightSpline->UpdateSpline();
	LeftSpline->UpdateSpline();

	Super::OnConstruction(Transform);
}

TArray<USplineComponent*> ASplineRepeater::GetSplines() const
{
	return { RootSpline, LeftSpline, RightSpline };
}
