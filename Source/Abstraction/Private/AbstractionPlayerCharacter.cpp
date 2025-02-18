#include "AbstractionPlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/DamageType.h"
#include "HealthComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/InputComponent.h"
#include "DamageHandlerComponent.h"

// Sets default values
AAbstractionPlayerCharacter::AAbstractionPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	DamageHandlerComponent = CreateDefaultSubobject<UDamageHandlerComponent>(TEXT("DamageHandlerComponent"));
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAbstractionPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//use possess/unpossess
	PC = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void AAbstractionPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAbstractionPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	FInputActionBinding* Binding;
	//these functions fire off events
	//interaction component listens to them
	Binding = &PlayerInputComponent->BindAction(FName("InteractionStart"), IE_Pressed, this, &AAbstractionPlayerCharacter::InteractionStartRequested);
	Binding = &PlayerInputComponent->BindAction(FName("InteractionCancel"), IE_Pressed, this, &AAbstractionPlayerCharacter::InteractionCancelRequested);
}

void  AAbstractionPlayerCharacter::FellOutOfWorld(const UDamageType& dmgType)
{
	if (HealthComponent && !HealthComponent->IsDead())
	{
		HealthComponent->SetCurrentHealth(0.0f);
		OnDeath(true);
	}	
}

float AAbstractionPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("AAbstractionPlayerCharacter::TakeDamage Damage %.2f"), Damage);
	if (HealthComponent)
	{
		HealthComponent->TakeDamage(Damage);
		if (HealthComponent->IsDead())
		{
			OnDeath(false);
		}
	}
	return Damage;
}

const bool AAbstractionPlayerCharacter::IsAlive() const
{
	if (HealthComponent)
	{
		return !HealthComponent->IsDead();
	}
	return false;
}

const float AAbstractionPlayerCharacter::GetCurrentHealth() const
{
	if (HealthComponent)
	{
		return !HealthComponent->GetCurrentHealth();
	}
	return 0.0f;
}

void AAbstractionPlayerCharacter::SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval)
{
	if (DamageHandlerComponent)
	{
		DamageHandlerComponent->TakeFireDamage(BaseDamage, DamageTotalTime, TakeDamageInterval);
	}
}

void AAbstractionPlayerCharacter::OnDeath(bool IsFellOut)
{

	GetWorld()->GetTimerManager().SetTimer(RestartLevelTimeHandle, this, &AAbstractionPlayerCharacter::OnDeathTimerFinished, TimeRestartLevelAfterDeath, false);

	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}

void AAbstractionPlayerCharacter::OnDeathTimerFinished()
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}

}

void AAbstractionPlayerCharacter::InteractionStartRequested()
{
	OnInteractionStartRequested.Broadcast();
}

void AAbstractionPlayerCharacter::InteractionCancelRequested()
{
	OnInteractionCancelRequested.Broadcast();
}

void AAbstractionPlayerCharacter::HandleItemCollected()
{
	ItemsCollected++;
	////Play Effects here.
	PC->PlayerCameraManager->StartCameraShake(CamShake,1.0f);
	/*PC->PlayDynamicForceFeedback(ForceFeedbackIntensity, ForceFeedbackDuration, true, false, true, false,EDynamicForceFeedbackAction::Start);*/

	ItemCollected();
}
