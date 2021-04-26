#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageTypes.generated.h"

/** Reduced by armor. */
UCLASS()
class UPhysicalDamage : public UDamageType
{
	GENERATED_BODY()
};

/** Reduced by magic resistance. */
UCLASS()
class UMagicalDamage : public UDamageType
{
	GENERATED_BODY()
};

/** Unaffected by armor or magic resistance. */
UCLASS()
class UTrueDamage : public UDamageType
{
	GENERATED_BODY()
};
