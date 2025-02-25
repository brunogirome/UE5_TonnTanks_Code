#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	ProjectileMovementComponent->MaxSpeed = MaxSpeed;
	ProjectileMovementComponent->InitialSpeed = InitialSpeed;

	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>("Smoke Trail");
	ParticleSystemComponent->SetupAttachment(RootComponent);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (BaseMesh)
	{
		BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	}

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
				this,
				LaunchSound,
				GetActorLocation());
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

	if (AActor *owner = GetOwner())
	{
		if (OtherActor && OtherActor != this && OtherActor != owner)
		{
			if (AController *controller = owner->GetInstigatorController())
			{
				UGameplayStatics::ApplyDamage(
						OtherActor,
						Damage,
						controller,
						this,
						UDamageType::StaticClass());
			}

			if (HitCameraShakeClass && GetWorld())
			{
				if (APlayerController * playerController = GetWorld()->GetFirstPlayerController())
				{
					playerController->ClientStartCameraShake(HitCameraShakeClass);
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("AProjectile::OnHit - Can't get the owner controller."));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AProjectile::OnHit - Can't get the projectile Owner."));
	}

	Destroy();
	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
	}

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
				this,
				HitSound,
				GetActorLocation());
	}
}
