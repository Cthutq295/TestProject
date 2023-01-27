// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "AIHealthWidget.generated.h"

UCLASS()
class TESTPROJECT_API UAIHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthPercent(float HealthPercent);

	virtual void NativeOnInitialized() override;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;
};
