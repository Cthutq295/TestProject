#include "Player/BaseCharacter.h"

#include "AI/AICharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	LeftArmBoxComponent = CreateDefaultSubobject<UBoxComponent>("LeftBoxComponent");
	RightArmBoxComponent = CreateDefaultSubobject<UBoxComponent>("RightBoxComponent");

	LeftArmBoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	RightArmBoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

	LeftArmBoxComponent->IgnoreActorWhenMoving(GetOwner(), true);
	RightArmBoxComponent->IgnoreActorWhenMoving(GetOwner(), true);

	LeftArmBoxComponent->SetGenerateOverlapEvents(false);
	RightArmBoxComponent->SetGenerateOverlapEvents(false);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddUObject(this, &ABaseCharacter::OnDeath);

	SetupBoxAttachment();

	LeftArmBoxComponent->SetWorldScale3D(FVector(0.15));
	RightArmBoxComponent->SetWorldScale3D(FVector(0.15));

	LeftArmBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnAttackHit);
	RightArmBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnAttackHit);
}

void ABaseCharacter::AttackPrimal()
{
	if (GetCharacterMovement()->IsFalling() || PrimalAttackMontage.IsEmpty() || !CanAttack) return;

	UAnimMontage* RandomAnim = PrimalAttackMontage[FMath::RandRange(0, PrimalAttackMontage.Num() - 1)];
	if (!RandomAnim) return;

	CurrentMontage = RandomAnim;

	LeftArmBoxComponent->SetGenerateOverlapEvents(true);
	RightArmBoxComponent->SetGenerateOverlapEvents(true);

	GetCharacterMovement()->DisableMovement();
	CanAttack = false;
	PlayAnimMontage(RandomAnim);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ABaseCharacter::PostAttack, RandomAnim->GetPlayLength(),
	                                false);
}

void ABaseCharacter::AttackSecondary()
{
	if (GetCharacterMovement()->IsFalling() || SecondaryAttackMontage.IsEmpty() || !CanAttack) return;

	UAnimMontage* RandomAnim = SecondaryAttackMontage[FMath::RandRange(0, SecondaryAttackMontage.Num() - 1)];
	if (!RandomAnim) return;

	CurrentMontage = RandomAnim;

	LeftArmBoxComponent->SetGenerateOverlapEvents(true);
	RightArmBoxComponent->SetGenerateOverlapEvents(true);
	

	FinalDamage += DamageBonus;
	
	GetCharacterMovement()->DisableMovement();
	CanAttack = false;
	PlayAnimMontage(RandomAnim);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ABaseCharacter::PostAttack, RandomAnim->GetPlayLength(),
	                                false);
}

void ABaseCharacter::PostAttack()
{
	CanAttack = true;
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	LeftArmBoxComponent->SetGenerateOverlapEvents(false);
	RightArmBoxComponent->SetGenerateOverlapEvents(false);

	FinalDamage = Damage;
}

void ABaseCharacter::OnAttackHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp,
                                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Check if we clipping through wall
	if (OtherComp == Cast<UStaticMeshComponent>(OtherComp))
	{
		StopAnimMontage(CurrentMontage);
		GetWorldTimerManager().ClearTimer(AttackTimerHandle);
		PostAttack();
		return;
	}
}

void ABaseCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(RagdollTimeExistence);
	GetCapsuleComponent()->SetCollisionResponseToChannels(ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	GetMesh()->SetSimulatePhysics(true);
}

void ABaseCharacter::Dash()
{
}

void ABaseCharacter::SetupBoxAttachment()
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	LeftArmBoxComponent->AttachToComponent(GetMesh(), AttachmentRules, "hand_lSocket");
	RightArmBoxComponent->AttachToComponent(GetMesh(), AttachmentRules, "hand_rSocket");
}
