#pragma once

#include "CoreMinimal.h"
#include "TowerActionContext.h"
#include "UObject/Object.h"
#include "TowerAction.generated.h"

class UTexture2D;

UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class UTowerAction : public UObject
{
	GENERATED_BODY()

public:

	UTowerAction();

	UFUNCTION(BlueprintPure, Category = Display)
	FText GetDisplayName() const;

	UFUNCTION(BlueprintPure, Category = Display)
	UTexture2D* GetDisplayIcon() const;

	UFUNCTION(BlueprintPure, Category = Display)
	float GetMenuAngle();

	UFUNCTION(BlueprintPure, Category = Cost)
	int32 GetCost() const;

	UFUNCTION(BlueprintPure, Category = Selection)
	bool RequiresConfirm() const;

	virtual void Select(const FTowerActionContext& Context);
	virtual void Unselect(const FTowerActionContext& Context);

	virtual bool CanExecute(const FTowerActionContext& Context);
	virtual void Execute(const FTowerActionContext& Context);

protected:

	void UnselectTowerBerth(const FTowerActionContext& Context);

	UPROPERTY(EditAnywhere, Category = Display)
	FText Name;

	UPROPERTY(EditAnywhere, Category = Display)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, Category = Display)
	float MenuAngle;

	UPROPERTY(EditAnywhere, Category = Cost)
	int32 Cost;
	
	UPROPERTY(BlueprintReadOnly, Category = Selection, Meta=(AllowPrivateAccess="true"))
	bool bRequiresConfirm;
};