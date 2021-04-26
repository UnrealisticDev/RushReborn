#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectableInterface.generated.h"

class ISelectorInterface;

/**
 * Exposes common functionality for anything
 * that can be selected by anything else.
 * Pairs with ISelectorInterface.
 */
UINTERFACE()
class USelectableInterface : public UInterface
{
	GENERATED_BODY()
};

class ISelectableInterface
{
	GENERATED_BODY()

public:

	/** Acknowledge selection by selector. */
	virtual void OnSelected(ISelectorInterface* Selector) {}

	/** Acknowledge unselection by selector. */
	virtual void OnUnselected(ISelectorInterface* Selector) {}
};
