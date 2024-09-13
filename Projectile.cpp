#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	ProjectileMovementComponent->InitialSpeed = InitialSpeed;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (BaseMesh)
	{
		BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(
		UPrimitiveComponent *HitComp,
		AActor *OtherActor,
		UPrimitiveComponent *OtherComp,
		FVector NormalImpulse,
		const FHitResult &Hit)
{
	UE_LOG(LogTemp, Display, TEXT("The dood shooting: %s - HitComp: %s, OtherActor: %s, OtherComp: %s"),
				 *GetActorNameOrLabel(),
				 *HitComp->GetName(),
				 *OtherActor->GetName(),
				 *OtherComp->GetName());
}