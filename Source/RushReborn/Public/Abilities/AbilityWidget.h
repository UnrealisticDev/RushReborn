#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityWidget.generated.h"

class UAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSelected);

UCLASS(Blueprintable)
class UAbilityWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct();

	UFUNCTION(BlueprintPure)
	bool CanBeSelected() const;

	UFUNCTION(BlueprintCallable)
	void Select();

	UPROPERTY(BlueprintAssignable)
	FOnSelected OnSelected;

	UFUNCTION(BlueprintCallable)
	void Unselect();

private:

	void CacheTargetAbility();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAbility> TargetAbilityClass;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TWeakObjectPtr<const UAbility> TargetAbility;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	bool bIsSelected;
};
