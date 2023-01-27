#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "AttackEnemyService.generated.h"
UCLASS()
class TESTPROJECT_API UAttackEnemyService : public UBTService
{
	GENERATED_BODY()
public:
	UAttackEnemyService();

protected:
	UPROPERTY(EditAnywhere, Category="AI")
	FBlackboardKeySelector EnemyActorKey;

	UPROPERTY(EditAnywhere)
	float MinAttackRange = 100.f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
