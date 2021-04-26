#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EngagementInterfaces.generated.h"

class IEngageeInterface;

/**
 * Exposes functionality for engaging
 * an actor.
 */
UINTERFACE(Meta=(CannotImplementInterfaceInBlueprints))
class UEngagorInterface : public UInterface
{
	GENERATED_BODY()
};

class IEngagorInterface
{
	GENERATED_BODY()

public:

	/** Engage the specified target. */
	virtual void Engage(IEngageeInterface* Engagee) = 0;

	/** Disengage from the current target, if any. */
	virtual void Disengage() = 0;

	/** Get the current target. */
	virtual IEngageeInterface* GetEngagee() const = 0;
};

/**
 * Exposes functionality for being
 * engaged by an actor.
 */
UINTERFACE(Meta=(CannotImplementInterfaceInBlueprints))
class UEngageeInterface : public UInterface
{
	GENERATED_BODY()
};

class IEngageeInterface
{
	GENERATED_BODY()

public:

	/** Acknowledge engagement by engagor. */
	virtual void EngagedBy(IEngagorInterface* Engagor) = 0;

	/** Acknowledge disengagement by engagor. */
	virtual void DisengagedBy(IEngagorInterface* Engagor) = 0;

	/** Returns true if engaged by anyone. */
	virtual bool IsEngaged() const = 0;

	/** Get number of engagors. */
	virtual int32 GetEngagementCount() const = 0;
};
