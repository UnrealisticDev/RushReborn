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
