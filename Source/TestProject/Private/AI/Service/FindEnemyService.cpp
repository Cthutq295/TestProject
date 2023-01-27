#include "AI/Service/FindEnemyService.h"

#include "AIController.h"
#include "AI/Components/EnemyAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindEnemyService::UFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if (BlackBoard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Controller->FindComponentByClass<UEnemyAIPerceptionComponent>();
		if (PerceptionComponent)
		{
			BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
