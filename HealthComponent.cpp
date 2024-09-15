#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthValue = MaxHealth;

	if (AActor *owner = GetOwner())
	{
		owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamageTaken);
	}
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
}