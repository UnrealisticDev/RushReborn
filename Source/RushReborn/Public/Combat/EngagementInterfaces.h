#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EngagementInterfaces.generated.h"

class IEngageeInterface;

UINTERFACE(Meta=(CannotImplementInterfaceInBlueprints))
class UEngagorInterface : public UInterface
{
	GENERATED_BODY()
};

class IEngagorInterface
{
	GENERATED_BODY()

public:

	virtual void Engage(IEngageeInterface* Engagee) = 0;
	virtual void Disengage() = 0;
};

UINTERFACE(Meta=(CannotImplementInterfaceInBlueprints))
class UEngageeInterface : public UInterface
{
	GENERATED_BODY()
};

class IEngageeInterface
{
	GENERATED_BODY()

public:

	virtual void EngagedBy(IEngagorInterface* Engagor) = 0;
	virtual void DisengagedBy(IEngagorInterface* Engagor) = 0;
	virtual bool IsEngaged() const = 0;
};
