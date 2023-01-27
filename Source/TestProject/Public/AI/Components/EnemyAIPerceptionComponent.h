#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyAIPerceptionComponent.generated.h"

UCLASS()
class TESTPROJECT_API UEnemyAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:

	AActor* GetClosestEnemy() const;
	
};
