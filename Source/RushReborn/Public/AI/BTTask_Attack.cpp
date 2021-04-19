#include "BTTask_Attack.h"
#include "AIController.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Combat/StatsComponent.h"
#include "Combat/CombatantInterface.h"

UBTTask_Attack::UBTTask_Attack()
{
	bCreateNodeInstance = true;
}

uint16 UBTTask_Attack::GetInstanceMemorySize() const
{
	return sizeof(FBTAttackTaskMemory);
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Attacker = OwnerComp.GetAIOwner()->GetPawn();
	UStatsComponent* AttackerStats = Cast<UStatsComponent>(Attacker->GetComponentByClass(UStatsComponent::StaticClass()));
	if (AttackerStats == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	float AttackRate = AttackerStats->AttackRate;
	
	AActor* AttackTarget = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName));

	FBTAttackTaskMemory* State = (FBTAttackTaskMemory*)NodeMemory;
	FTimerDelegate AttackDelegate;
	AttackDelegate.BindUObject(this, &UBTTask_Attack::Attack, &OwnerComp, Attacker, AttackTarget);
	GetWorld()->GetTimerManager().SetTimer(State->AttackTimer, AttackDelegate, AttackRate, true, 0.01f);

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::Attack(UBehaviorTreeComponent* OwnerComp, AActor* Attacker, AActor* AttackTarget)
{
	Cast<ICombatantInterface>(Attacker)->Attack(AttackTarget);

	if (!Cast<ICombatantInterface>(AttackTarget)->IsAlive())
	{
		OwnerComp->GetBlackboardComponent()->SetValueAsObject(Target.SelectedKeyName, nullptr);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, TEXT("Aborting"));
	}
}

EBTNodeResult::Type UBTTask_Attack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FBTAttackTaskMemory* State = (FBTAttackTaskMemory*)NodeMemory;
	GetWorld()->GetTimerManager().ClearTimer(State->AttackTimer);
	
	return EBTNodeResult::Aborted;
}
