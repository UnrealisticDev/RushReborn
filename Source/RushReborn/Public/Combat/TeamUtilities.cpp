#include "TeamUtilities.h"
#include "TeamInterface.h"

bool UTeamUtilities::AreAllies(AActor* A, AActor* B)
{
	ITeamAgentInterface* TeamAgentA = Cast<ITeamAgentInterface>(A);
	ITeamAgentInterface* TeamAgentB = Cast<ITeamAgentInterface>(B);

	if (!TeamAgentA || !TeamAgentB)
	{
		return false;
	}

	return TeamAgentA->GetTeamId() == TeamAgentB->GetTeamId();
}

bool UTeamUtilities::AreEnemies(AActor* A, AActor* B)
{
	ITeamAgentInterface* TeamAgentA = Cast<ITeamAgentInterface>(A);
	ITeamAgentInterface* TeamAgentB = Cast<ITeamAgentInterface>(B);

	if (!TeamAgentA || !TeamAgentB)
	{
		return false;
	}

	return TeamAgentA->GetTeamId() != TeamAgentB->GetTeamId();
}
