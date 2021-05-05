#include "SplineRepeater.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"

ASplineRepeater::ASplineRepeater()
	: LateralOffset(50.f)
{
	RootSpline = CreateDefaultSubobject<USplineComponent>(TEXT("RootSpline"));
	RootSpline->SetMobility(EComponentMobility::Static);
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
	RepeatPathsAndInitTargeting();

	Super::OnConstruction(Transform);
}

void ASplineRepeater::BeginPlay()
{
	Super::BeginPlay();

	RepeatPathsAndInitTargeting();
}

TArray<USplineComponent*> ASplineRepeater::GetSplines() const
{
	return { RootSpline, LeftSpline, RightSpline };
}

void ASplineRepeater::RepeatPathsAndInitTargeting()
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

	float Distance = 0.f;
	while (Distance < RootSpline->GetDistanceAlongSplineAtSplinePoint(RootSpline->GetNumberOfSplinePoints() - 1))
	{
		UBoxComponent* Box = NewObject<UBoxComponent>(this);
		Box->CreationMethod = EComponentCreationMethod::UserConstructionScript;
		Box->SetupAttachment(GetRootComponent());
		Box->SetBoxExtent(FVector(20.f, LateralOffset * 1.7f, 30.f));
		Box->SetRelativeLocation(RootSpline->GetLocationAtDistanceAlongSpline(Distance, CoordinateSpace));
		Box->SetRelativeRotation(RootSpline->GetRotationAtDistanceAlongSpline(Distance, CoordinateSpace));
		Box->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
		Box->RegisterComponent();
			
		Distance += 20.f;
	}
}
