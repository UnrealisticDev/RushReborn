#include "Ability.h"
#include "Engine/World.h"
#include "TimerManager.h"

UAbility::UAbility()
	: Cooldown(99.f)
{

}

void UAbility::CanActivate(const FAbilityPayload& Payload)
{
	return true;
}

void UAbility::Activate(const FAbilityPayload& Payload)
{
	check(!IsOnCooldown());
	GetWorld()->GetTimerManager().SetTimer(CooldownTimer, []() {/* no op */}, Cooldown, false);
}

bool UAbility::IsOnCooldown() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(CooldownTimer);
}

float UAbility::GetCooldown() const
{
	return Cooldown;
}

float UAbility::GetCooldownElapsed() const
{
	return GetWorld()->GetTimerManager().GetTimerElapsed(CooldownTimer);
}

float UAbility::GetCooldownRemaining() const
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(CooldownTimer);
}

FText UAbility::GetTitle() const
{
	return Title;
}

FText UAbility::GetDescription() const
{
	return Description;
}

UTexture2D* UAbility::GetIcon() const
{
	return Icon;
}
