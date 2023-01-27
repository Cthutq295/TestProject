#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Player/BaseCharacter.h"
#include "AICharacter.generated.h"

UCLASS()
class TESTPROJECT_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AAICharacter();

	UPROPERTY(EditDefaultsOnly, Category="Health")
	UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(EditAnywhere, Category="AI")
	UBehaviorTree* BehaviorTree;

protected:

	virtual void BeginPlay() override;

	virtual void OnDeath() override;

	void OnHealthChanged(float Health);

	virtual void OnAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                         const FHitResult& SweepResult) override;
};
