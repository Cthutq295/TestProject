#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/EnemyAIPerceptionComponent.h"
#include "EnemyAIController.generated.h"

UCLASS()
class TESTPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	UPROPERTY()
	AActor* FocusedActor;

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UEnemyAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(EditAnywhere, Category="AI")
	FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor() const;
};
