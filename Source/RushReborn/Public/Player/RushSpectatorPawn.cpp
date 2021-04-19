#include "RushSpectatorPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ARushSpectatorPawn::ARushSpectatorPawn()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->TargetArmLength = 1200.f;
	SpringArmComponent->SetWorldRotation(FRotator(-30, 0, 0));
	SetRootComponent(SpringArmComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

uint8 ARushSpectatorPawn::GetTeamId()
{
	return Cast<ITeamAgentInterface>(GetController())->GetTeamId();
}
