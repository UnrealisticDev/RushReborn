#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityWidget.generated.h"

class UAbility;

UCLASS(Blueprintable)
class UAbilityWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct();

	UFUNCTION(BlueprintPure)
	bool CanBeSelected() const;

	UFUNCTION(BlueprintPure)
	bool IsSelected() const;

	UFUNCTION(BlueprintCallable)
	void Select();

	UFUNCTION(BlueprintCallable)
	void Unselect();

private:

	void CacheTargetAbility();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAbility> TargetAbilityClass;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TWeakObjectPtr<const UAbility> TargetAbility;
};
