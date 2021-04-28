#include "SplineRepeater.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

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

		if (i < RootSpline->GetNumberOfSplinePoints() - 1)
		{
			USplineMeshComponent* Mesh = NewObject<USplineMeshComponent>(this);
			Mesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
			Mesh->SetupAttachment(GetRootComponent());
			Mesh->RegisterComponent();
			Mesh->SetStaticMesh(CollisionMesh);
			Mesh->SetStartAndEnd
			(
				RootLocation,
				RootTangent,
				RootSpline->GetLocationAtSplinePoint(i + 1, CoordinateSpace),
				RootSpline->GetTangentAtSplinePoint(i + 1, CoordinateSpace)
			);
			Mesh->SetStartScale(FVector2D((LateralOffset / 100.f) * 3.4f, 1.f));
			Mesh->SetEndScale(FVector2D((LateralOffset / 100.f) * 3.4f, 1.f));
			Mesh->SetForwardAxis(ESplineMeshAxis::Z);
			Mesh->SetCollisionProfileName(TEXT("BlockAll"));
			Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1 /* Targeting */, ECollisionResponse::ECR_Block);
			Mesh->bHiddenInGame = true;
		}
	}

	RightSpline->UpdateSpline();
	LeftSpline->UpdateSpline();

	Super::OnConstruction(Transform);
}

TArray<USplineComponent*> ASplineRepeater::GetSplines() const
{
	return { RootSpline, LeftSpline, RightSpline };
}
