#include "Player/UI/PlayerHUD.h"

#include "Blueprint/UserWidget.h"

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!HealthWidgetClass) return;

	const auto PlayerHealthWidget = CreateWidget(GetWorld(), HealthWidgetClass);
	if (PlayerHealthWidget) PlayerHealthWidget->AddToViewport();
}
