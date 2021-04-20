#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectorInterface.generated.h"

class ISelectableInterface;

UINTERFACE()
class USelectorInterface : public UInterface
{
	GENERATED_BODY()
};

class ISelectorInterface
{
	GENERATED_BODY()

public:

	virtual void Select(ISelectableInterface* Selectable) {}
	virtual void Unselect(ISelectableInterface* Selectable) {}
	virtual ISelectableInterface* GetCurrentSelection() { return nullptr; }
};
