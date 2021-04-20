#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectableInterface.generated.h"

class ISelectorInterface;

UINTERFACE()
class USelectableInterface : public UInterface
{
	GENERATED_BODY()
};

class ISelectableInterface
{
	GENERATED_BODY()

public:

	virtual void OnSelected(ISelectorInterface* Selector) {}
	virtual void OnUnselected(ISelectorInterface* Selector) {}
};
