#include "AI/AICharacter.h"

#include "AI/AIHealthWidget.h"
#include "AI/EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"

AAICharacter::AAICharacter()
{
	HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidget");
	HealthWidgetComponent->SetupAttachment(GetRootComponent());
	HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEnemyAIController::StaticClass();
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHealthChanged.AddUObject(this, &AAICharacter::OnHealthChanged);
}

void AAICharacter::OnDeath()
{
	Super::OnDeath();
	const auto AIController = Cast<AAIController>(Controller);
	if (AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
	}
}

void AAICharacter::OnHealthChanged(float Health)
{
	const auto HealthBarWidget = Cast<UAIHealthWidget>(HealthWidgetComponent->GetUserWidgetObject());
	if (!HealthBarWidget) return;
	HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AAICharacter::OnAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	Super::OnAttackHit(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	auto Character = Cast<APlayerCharacter>(OtherActor);
	if (OtherActor == Character)
	{
		UGameplayStatics::ApplyDamage(Character, FinalDamage, GetController(), GetOwner(), nullptr);

		// Apply damage only once and to only first encountered character
		LeftArmBoxComponent->SetGenerateOverlapEvents(false);
		RightArmBoxComponent->SetGenerateOverlapEvents(false);
	}
}
