#include "Player/UI/HealthWidget.h"

#include "Player/BaseCharacter.h"

void UHealthWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (!HealthProgressBar) return;

	const auto Player = Cast<ABaseCharacter>(GetOwningPlayerPawn());
	if (!Player) return;

	HealthComponent = Cast<UHealthComponent>(Player->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!HealthComponent) return;

	HealthComponent->OnHealthChanged.AddUObject(this, &UHealthWidget::OnHealthChanged);
	HealthProgressBar->SetPercent(HealthComponent->GetHealthPercent());
}

void UHealthWidget::OnHealthChanged(float Health)
{
	HealthProgressBar->SetPercent(HealthComponent->GetHealthPercent());
}