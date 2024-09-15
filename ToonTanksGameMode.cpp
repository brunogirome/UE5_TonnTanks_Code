#include "ToonTanksGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "TankController.h"
#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
  if (Tank && DeadActor == Tank)
  {
    Tank->HandleDestruction();
    if (TankController)
    {
      TankController->SetPlayerEnableState(fa);
    }
  }
  else if (auto tower = Cast<ATower>(DeadActor))
  {
    tower->HandleDestruction();
  }
}

void AToonTanksGameMode::BeginPlay()
{
  Super::BeginPlay();

  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
  TankController = Cast<ATankController>(UGameplayStatics::GetPlayerController(this, 0));
}