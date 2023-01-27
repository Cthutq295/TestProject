#include "Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                       AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead()) return;

	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, 1000.f);
	OnHealthChanged.Broadcast(CurrentHealth);

	if (FMath::IsNearlyZero(CurrentHealth))
	{
		OnDeath.Broadcast();
		CurrentHealth = 0.0f;
	}
}
