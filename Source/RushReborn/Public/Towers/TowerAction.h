#pragma once

#include "CoreMinimal.h"
#include "TowerActionContext.h"
#include "UObject/Object.h"
#include "TowerAction.generated.h"

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class UTowerAction : public UObject
{
	GENERATED_BODY()

public:

	UTowerAction() {}

	virtual bool CanSelect(const FTowerActionContext& Context);
	virtual void Select(const FTowerActionContext& Context);
	virtual void Unselect(const FTowerActionContext& Context);
	virtual bool IsSelected();

	virtual void Execute(const FTowerActionContext& Context);

protected:

	UPROPERTY(BlueprintReadOnly, Category = Selection, Meta = (AllowPrivateAccess = "true"))
	bool bIsSelected;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Selection, Meta=(AllowPrivateAccess="true"))
	bool bRequiresConfirm;
};
