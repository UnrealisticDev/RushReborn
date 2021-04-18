#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageTypes.generated.h"

UCLASS()
class UPhysicalDamage : public UDamageType
{
	GENERATED_BODY()
};

UCLASS()
class UMagicalDamage : public UDamageType
{
	GENERATED_BODY()
};

UCLASS()
class UTrueDamage : public UDamageType
{
	GENERATED_BODY()
};
