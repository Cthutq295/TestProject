#include "AI/Service/AttackEnemyService.h"

#include "AIController.h"
#include "AI/AICharacter.h"
#include "AI/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UAttackEnemyService::UAttackEnemyService()
{
	NodeName = "Attack Enemy";
}

void UAttackEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	const auto PerceptionComponent = Controller->FindComponentByClass<UEnemyAIPerceptionComponent>();

	const auto HasAim = BlackBoard && BlackBoard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Controller && PerceptionComponent && HasAim)
	{
		if(const AActor* Enemy = PerceptionComponent->GetClosestEnemy())
		{
			float Distance = (Controller->GetPawn()->GetActorLocation() - Enemy->GetActorLocation()).Size();
			if(Distance <= MinAttackRange)
			{
				Cast<AAICharacter>(Controller->GetPawn())->AttackPrimal();
			}	
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
