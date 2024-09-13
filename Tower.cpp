#include "Tower.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "Tank.h"

void ATower::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  FVector tankLocation;
  if (IsTankOnFireRange(tankLocation))
  {
    RotateTurret(tankLocation);
  }
}

void ATower::BeginPlay()
{
  Super::BeginPlay();

  if (ATank *player = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)))
  {
    Tank = player;
  }

  if (GetWorld())
  {
    GetWorldTimerManager().SetTimer(FireRateTimerHandler, this, &ATower::CheckFireCondition, FireRate, true);
  }
}

void ATower::CheckFireCondition()
{
  if (IsTankOnFireRange() && GetWorld())
  {
    Fire();
  }
}

bool ATower::IsTankOnFireRange(FVector &OutTankLocation)
{
  if (Tank)
  {
    FVector tankLocation = Tank->GetActorLocation();
    OutTankLocation = tankLocation;
    float distance = FVector::Dist(GetActorLocation(), OutTankLocation);

    return distance <= FireRange;
  }
  return false;
}

bool ATower::IsTankOnFireRange()
{
  FVector zeroVector = FVector::ZeroVector;
  return IsTankOnFireRange(zeroVector);
}