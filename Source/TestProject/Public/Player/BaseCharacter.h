#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Components/HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TESTPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Health")
	UHealthComponent* HealthComponent;

	ABaseCharacter();

	void AttackPrimal();
	void AttackSecondary();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	TArray<UAnimMontage*> PrimalAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	TArray<UAnimMontage*> SecondaryAttackMontage;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* RollMontage;

	UPROPERTY(EditAnywhere)
	float ImpulseForce = 100.f;

	UPROPERTY(EditAnywhere, Category = "Ragdoll")
	float RagdollTimeExistence = 5.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	UBoxComponent* LeftArmBoxComponent;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	UBoxComponent* RightArmBoxComponent;

	UPROPERTY(EditAnywhere, Category="Damage", meta=(ClampMin = 1))
	float Damage = 25;

	UPROPERTY(EditAnywhere, Category="Damage", meta=(ClampMin = 1))
	float DamageBonus = 25;

	float FinalDamage = Damage;

	virtual void BeginPlay() override;

	void PostAttack();

	UFUNCTION()
	virtual void OnAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp,
	                         int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnDeath();

	virtual void Dash();

	bool CanAttack = true;

	void SetupBoxAttachment();

	UAnimMontage* CurrentMontage;

	FTimerHandle AttackTimerHandle;
};
