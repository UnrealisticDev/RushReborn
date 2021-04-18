#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageTypes.generated.h"

UCLASS(Abstract)
class URushDamage : public UDamageType
{
	GENERATED_BODY()

public:

	UPROPERTY()
	float Magnitude;
};

UCLASS()
class UPhysicalDamage : public URushDamage
{
	GENERATED_BODY()
};

UCLASS()
class UMagicalDamage : public URushDamage
{
	GENERATED_BODY()
};

UCLASS()
class UTrueDamage : public URushDamage
{
	GENERATED_BODY()
};
