#include "RushSpectatorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"

ARushSpectatorPawn::ARushSpectatorPawn()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->TargetArmLength = 4700.f;
	SpringArmComponent->SetWorldRotation(FRotator(-45.f, 0, 0));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ARushSpectatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis
	(
		"MoveForward",
		this,
		&ARushSpectatorPawn::MoveForward
	);

	PlayerInputComponent->BindAxis
	(
		"MoveRight",
		this,
		&ARushSpectatorPawn::MoveRight
	);

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

	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARushSpectatorPawn::MoveForward(float AxisValue)
{
	AddActorWorldOffset(FVector(AxisValue * 50.f, 0.f, 0.f));
}

void ARushSpectatorPawn::MoveRight(float AxisValue)
{
	AddActorWorldOffset(FVector(0.f, AxisValue * 50.f, 0.f));
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
	float ZoomFinal = FMath::Clamp(SpringArmComponent->TargetArmLength + Delta, 1200.f, 4700.f);
	SpringArmComponent->TargetArmLength = ZoomFinal;
}
