#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "HomeBase.generated.h"

UCLASS()
class AHomeBase : public ATriggerBox
{
	GENERATED_BODY()

public:

	void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
