#include "AI/Components/EnemyAIPerceptionComponent.h"

#include "AIController.h"
#include "Components/HealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Player/PlayerCharacter.h"

AActor* UEnemyAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PerceiveActor : PerceiveActors)
	{
		const auto Player = Cast<APlayerCharacter>(PerceiveActor);
		const auto HealthComponent = PerceiveActor->FindComponentByClass<UHealthComponent>();
		if (HealthComponent && !HealthComponent->IsDead() && Player)
		{
			const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestPawn = PerceiveActor;
				BestDistance = CurrentDistance;
			}
		}
	}

	return BestPawn;
}
