#include "Tower.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"

void ATower::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if (Tank)
  {
    FVector tankLocation = Tank->GetActorLocation();
    float distance = FVector::Dist(GetActorLocation(), tankLocation);

    if (distance <= FireRange)
    {
      RotateTurret(tankLocation);
    }
  }
}

void ATower::BeginPlay()
{
  Super::BeginPlay();

  if (ATank *player = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)))
  {
    Tank = player;
  }
}
