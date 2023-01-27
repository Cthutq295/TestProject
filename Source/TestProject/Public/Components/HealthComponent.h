#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	float GetHealthPercent() const { return CurrentHealth / MaxHealth; };
	float GetHealth() const { return CurrentHealth; };

	bool IsDead() const { return FMath::IsNearlyZero(CurrentHealth) ? true : false; }

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

protected:
	UPROPERTY(EditAnywhere, Category = "Health", meta=(ClampMin = 1.0f))
	float MaxHealth = 100.f;

	virtual void BeginPlay() override;

private:
	float CurrentHealth;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
	                     class AController* InstigatedBy, AActor* DamageCauser);
};
