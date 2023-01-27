// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIHealthWidget.h"

void UAIHealthWidget::SetHealthPercent(float HealthPercent)
{
	if (!HealthBar) return;

	const auto HealthBarVisibility = (HealthPercent == 1.0 || FMath::IsNearlyZero(HealthPercent))
		                                 ? ESlateVisibility::Hidden
		                                 : ESlateVisibility::Visible;

	HealthBar->SetVisibility(HealthBarVisibility);
	HealthBar->SetPercent(HealthPercent);
}

void UAIHealthWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(HealthBar->GetPercent() == 1.0f)  HealthBar->SetVisibility(ESlateVisibility::Hidden);
}
