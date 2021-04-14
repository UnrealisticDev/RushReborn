#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Ability.generated.h"

USTRUCT()
struct FAbilityPayload
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FVector Location;
};

class UTexture2D;
class UWorld;

UCLASS(Abstract)
class UAbility : public UObject
{
	GENERATED_BODY()

public:

	UAbility();

	virtual void Activate(const FAbilityPayload& Payload);

	UFUNCTION(BlueprintPure, Category = "Status")
	bool IsOnCooldown() const;

	UFUNCTION(BlueprintPure, Category = "Status")
	float GetCooldown() const;

	UFUNCTION(BlueprintPure, Category = "Status")
	float GetCooldownElapsed() const;

	UFUNCTION(BlueprintPure, Category = "Status")
	float GetCooldownRemaining() const;

	UFUNCTION(BlueprintPure, Category = "Display")
	FText GetTitle() const;
	
	UFUNCTION(BlueprintPure, Category = "Display")
	FText GetDescription() const;

	UFUNCTION(BlueprintPure, Category = "Display")
	UTexture2D* GetIcon() const;

protected:

	UPROPERTY()
	FText Title;

	UPROPERTY()
	FText Description;

	UPROPERTY()
	UTexture2D* Icon;

	UPROPERTY()
	float Cooldown;

	UPROPERTY()
	FTimerHandle CooldownTimer;
};
