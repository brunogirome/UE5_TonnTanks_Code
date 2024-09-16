#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UPrimitiveComponent;
class UParticleSystem;
class UParticleSystemComponent;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent *ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent *ParticleSystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float InitialSpeed = 40.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	float Damage = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	UParticleSystem *HitParticles;

	UFUNCTION()
	void OnHit(
			UPrimitiveComponent *HitComp,
			AActor *OtherActor,
			UPrimitiveComponent *OtherComp,
			FVector NormalImpulse,
			const FHitResult &Hit);
};
