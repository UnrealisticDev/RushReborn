#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "HomeBase.generated.h"

/**
 * The HomeBase is a minimal trigger box that
 * reduces global health whenever another actor
 * overlaps it. It destroys the overlapping actor.
 */
UCLASS(Config=Game)
class AHomeBase : public ATriggerBox
{
	GENERATED_BODY()

public:

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:

	/** The sound to play on overlap. */
	UPROPERTY(Config)
	FSoftObjectPath OverlapCue;
};
