#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TeamUtilities.generated.h"

class AActor;

UCLASS()
class UTeamUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static bool AreAllies(AActor* A, AActor* B);

	UFUNCTION(BlueprintCallable)
	static bool AreEnemies(AActor* A, AActor* B);
};
