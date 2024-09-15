#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"

#include "ToonTanksGameMode.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthValue = MaxHealth;

	if (auto owner = GetOwner())
	{
		owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamageTaken);
	}
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::OnDamageTaken(AActor *DamagedActor, float Damage, const UDamageType *DamageType, AController *Instigator, AActor *DamageCauser)
{
	if (Damage > 0)
	{
		HealthValue = FMath::Clamp(HealthValue - Damage, 0, MaxHealth);
	}

	if (HealthValue <= 0 && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(GetOwner());
	}
}