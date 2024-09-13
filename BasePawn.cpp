#include "BasePawn.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

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
	if (ProjectileSpawnPoint)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), SpawnLocation, 30.f, 12, FColor::Red, 3.f, 1.f);

		UE_LOG(LogTemp, Display, TEXT("FIRE DEEZ NUTS"));
	}
}
