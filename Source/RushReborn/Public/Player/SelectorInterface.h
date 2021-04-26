#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectorInterface.generated.h"

class ISelectableInterface;

/**
 * Exposes common functionality for anything
 * that wants to select anything else.
 * Pairs with ISelectableInterface.
 */
UINTERFACE()
class USelectorInterface : public UInterface
{
	GENERATED_BODY()
};

class ISelectorInterface
{
	GENERATED_BODY()

public:

	/** Select the specified selectable. */
	virtual void Select(ISelectableInterface* Selectable) {}

	/** Unselect the specified selectable. */
	virtual void Unselect(ISelectableInterface* Selectable) {}

	/** Get the current selection, if any. */
	virtual ISelectableInterface* GetCurrentSelection() { return nullptr; }
};
