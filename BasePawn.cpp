#include "BasePawn.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Projectile.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	BaseMesh->SetupAttachment(RootComponent);
	TurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>("Turrent Mesh");
	TurrentMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(TurrentMesh);
}

void ABasePawn::HandleDestruction()
{
	if (ExplosionParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticles, GetActorLocation(), GetActorRotation());
	}
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
				this,
				ExplosionSound,
				GetActorLocation());
	}
}

void ABasePawn::RotateTurret(const FVector AimPosition)
{
	if (TurrentMesh)
	{
		float deltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);

		FVector ToTaget = AimPosition - TurrentMesh->GetComponentLocation();
		FRotator AngleToTarget = FRotator(0.f, ToTaget.Rotation().Yaw, 0.f);
		TurrentMesh->SetWorldRotation(
				FMath::RInterpTo(
						TurrentMesh->GetComponentRotation(),
						AngleToTarget,
						deltaSeconds,
						25.f));
	}
}

void ABasePawn::Fire()
{
	if (GetWorld() && ProjectileSpawnPoint)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		auto projectile = GetWorld()->SpawnActor<AProjectile>(BP_ProjectileClass, SpawnLocation, SpawnRotation);
		projectile->SetOwner(this);
	}
}
