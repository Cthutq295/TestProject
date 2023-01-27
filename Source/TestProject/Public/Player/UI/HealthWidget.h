#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HealthComponent.h"
#include "Components/ProgressBar.h"
#include "HealthWidget.generated.h"

UCLASS()
class TESTPROJECT_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void OnHealthChanged(float Health);

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
	UHealthComponent* HealthComponent;
	
};
