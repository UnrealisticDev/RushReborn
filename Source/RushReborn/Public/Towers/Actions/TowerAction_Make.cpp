#include "TowerAction_Make.h"
#include "Components/DecalComponent.h"
#include "Towers/TowerBerth.h"
#include "Framework/TowerDefenseEssentialsInterface.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Towers/Tower.h"
#include "Engine/DecalActor.h"

UTowerAction_Make::UTowerAction_Make()
{
	bRequiresConfirm = true;
}

void UTowerAction_Make::Select(const FTowerActionContext& Context)
{
	check(TowerClass);

	ATower* TowerDefault = TowerClass.GetDefaultObject();
	
	RangeIndicator = Cast<ADecalActor>(GetWorld()->SpawnActorAbsolute(ADecalActor::StaticClass(), Context.TowerBerth->GetActorTransform()));
	RangeIndicator->AddActorLocalRotation(FRotator(-90, 0, 0));
	RangeIndicator->GetDecal()->DecalSize = FVector
	(
		15.f,
		TowerDefault->GetInfluenceRadius(),
		TowerDefault->GetInfluenceRadius()
	);
	RangeIndicator->SetDecalMaterial(Cast<UMaterialInterface>(RangeIndicatorMaterial.TryLoad()));
}

void UTowerAction_Make::Unselect(const FTowerActionContext& Context)
{
	if (RangeIndicator)
	{
		RangeIndicator->Destroy();
	}
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
