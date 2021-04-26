#pragma once

#include "CoreMinimal.h"
#include "TowerActionContext.h"
#include "UObject/Object.h"
#include "TowerAction.generated.h"

class UTexture2D;

/**
 * A TowerAction is any selectable action
 * that can be taken on or with respect to
 * a tower. Supports actions that must be
 * confirmed and actions that are executed
 * on first select.
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class UTowerAction : public UObject
{
	GENERATED_BODY()

public:

	UTowerAction();

	/** Get the display name of this action. */
	UFUNCTION(BlueprintPure, Category = Display)
	FText GetDisplayName() const;

	/** Get the display icon of this action. */
	UFUNCTION(BlueprintPure, Category = Display)
	UTexture2D* GetDisplayIcon() const;

	/** Get the display radial angle of this action. */
	UFUNCTION(BlueprintPure, Category = Display)
	float GetMenuAngle();

	/** Get the cost of this action. */
	UFUNCTION(BlueprintPure, Category = Cost)
	int32 GetCost() const;

	/** Returns true if this action needs to be confirmed. */
	UFUNCTION(BlueprintPure, Category = Selection)
	bool RequiresConfirm() const;

	/** Selection callbacks. */
	virtual void Select(const FTowerActionContext& Context);
	virtual void Unselect(const FTowerActionContext& Context);

	/** Execution callbacks. */
	virtual bool CanExecute(const FTowerActionContext& Context);
	virtual void Execute(const FTowerActionContext& Context);

protected:

	/** Utility function to unselect source tower berth. */
	void UnselectTowerBerth(const FTowerActionContext& Context);

	/** Display name. */
	UPROPERTY(EditAnywhere, Category = Display)
	FText Name;

	/** Display icon. */
	UPROPERTY(EditAnywhere, Category = Display)
	UTexture2D* Icon;

	/** Display angle in radial menu. */
	UPROPERTY(EditAnywhere, Category = Display)
	float MenuAngle;

	/** Cost (in terms of global gold) to take this action. */
	UPROPERTY(EditAnywhere, Category = Cost)
	int32 Cost;

	/** Whether or not this action must be confirmed. */
	UPROPERTY(BlueprintReadOnly, Category = Selection, Meta=(AllowPrivateAccess="true"))
	bool bRequiresConfirm;
};
