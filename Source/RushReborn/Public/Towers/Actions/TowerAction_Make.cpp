#include "TowerAction_Make.h"
#include "Towers/TowerBerth.h"
#include "Framework/TowerDefenseEssentialsInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Towers/Tower.h"

UTowerAction_Make::UTowerAction_Make()
{
	bRequiresConfirm = true;
}

bool UTowerAction_Make::CanExecute(const FTowerActionContext& Context)
{
	return UGameplayStatics::GetGameMode(this)->Implements<UTowerDefenseEssentialsInterface>()
		? Cast<ITowerDefenseEssentialsInterface>(UGameplayStatics::GetGameMode(this))->GetGoldCount() >= Cost
		: false;
}

void UTowerAction_Make::Execute(const FTowerActionContext& Context)
{
	check(TowerClass);

	Cast<ITowerDefenseEssentialsInterface>(UGameplayStatics::GetGameMode(this))->AddGold(-Cost);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ATower* NewTower = Cast<ATower>(GetWorld()->SpawnActorAbsolute(TowerClass, Context.TowerBerth->GetActorTransform(), SpawnParams));
	Context.TowerBerth->SetTower(NewTower);

	UnselectTowerBerth(Context);
}
