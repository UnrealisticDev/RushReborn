#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TeamUtilities.generated.h"

class AActor;

/** Provides utilities for dealing with team agents. */
UCLASS()
class UTeamUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Returns true if both actors are on the same team.
	 * False otherwise, including if either actor does not implement ITeamAgentInterface.
	 */
	UFUNCTION(BlueprintCallable)
	static bool AreAllies(AActor* A, AActor* B);

	/**
	 * Returns true if both actors are not on the same team.
	 * False otherwise, including if either actor does not implement ITeamAgentInterface.
	 */
	UFUNCTION(BlueprintCallable)
	static bool AreEnemies(AActor* A, AActor* B);
};
