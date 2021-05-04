#include "RushSpectatorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ARushSpectatorPawn::ARushSpectatorPawn()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->TargetArmLength = 4700.f;
	SpringArmComponent->SetWorldRotation(FRotator(-45, 0, 0));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ARushSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindKey
	(
		EKeys::MouseScrollUp,
		IE_Pressed,
		this,
		&ARushSpectatorPawn::ZoomIn
	);

	PlayerInputComponent->BindKey
	(
		EKeys::MouseScrollDown,
		IE_Pressed,
		this,
		&ARushSpectatorPawn::ZoomOut
	);
}

float ZoomFactor = 300.f;

void ARushSpectatorPawn::ZoomIn()
{
	Zoom(-ZoomFactor);
}

void ARushSpectatorPawn::ZoomOut()
{
	Zoom(ZoomFactor);
}

void ARushSpectatorPawn::Zoom(float Delta)
{
	float ZoomFinal = FMath::Clamp(SpringArmComponent->TargetArmLength + Delta, 0.f, 4700.f);
	SpringArmComponent->TargetArmLength = ZoomFinal;
}
