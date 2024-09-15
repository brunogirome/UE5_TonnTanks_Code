#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

class ATank;
struct FTimerHandler;

UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	virtual void BeginPlay() override;

private:
	ATank *Tank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 600.f;

	FTimerHandle FireRateTimerHandler;

	float FireRate = 2.f;

	void CheckFireCondition();

	bool IsTankOnFireRange(FVector &OutTankLocation);

	bool IsTankOnFireRange();
};
