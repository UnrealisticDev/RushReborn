#pragma once

#include "CoreMinimal.h"
#include "Combat/CombatantInterface.h"
#include "Combat/EngagementInterfaces.h"
#include "Combat/TeamInterface.h"
#include "GameFramework/Character.h"
#include "Defender.generated.h"

class UWidgetComponent;
class UStatsComponent;

/**
 * A Defender is the base class for all
 * mobile pawns that defend the base. They are
 * on the player team and can engage enemies,
 * causing them to halt and fight to the death.
 */
UCLASS()
class ADefender : public ACharacter, public ITeamAgentInterface, public IEngagorInterface, public ICombatantInterface
{
	GENERATED_BODY()

public:

	ADefender();
	void BeginPlay() override;

	//~ Begin ITeamInterface
	uint8 GetTeamId() override;
	//~ End ITeamInterface

	//~ Begin IEngagorInterface
	void Engage(IEngageeInterface* Engagee) override;
	void Disengage() override;
	IEngageeInterface* GetEngagee() const override;
	//~ End IEngagorInterface

	//~ Begin ICombatantInterface
	bool IsAlive() const override;
	void Attack(AActor* Target) override;
	//~ Begin ICombatantInterface

	UFUNCTION()
	void OnHealthDepleted();

	void Destroyed() override;

protected:

	/** Healthbar widget. */
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* Healthbar;

	/** Stats component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStatsComponent* Stats;

private:

	/** Currently engaged actor. */
	UPROPERTY()
	TScriptInterface<IEngageeInterface> Engaged;
};
