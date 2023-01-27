#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NextLocationTask.generated.h"

UCLASS()
class TESTPROJECT_API UNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UNextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "AI")
	float Radius = 1000.f;

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AimLocationKey;
	
};
