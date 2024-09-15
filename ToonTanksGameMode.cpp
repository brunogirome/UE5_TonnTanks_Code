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
      TankController->SetPlayerEnableState(false);
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

  StartGame();

  Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
  TankController = Cast<ATankController>(UGameplayStatics::GetPlayerController(this, 0));

  HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
  if (TankController)
  {
    TankController->SetPlayerEnableState(false);

    FTimerHandle PlayerEnabledTimerHandle;

    FTimerDelegate InputTimerDelegate = FTimerDelegate::CreateUObject(
        TankController,
        &ATankController::SetPlayerEnableState,
        true);

    GetWorld()->GetTimerManager().SetTimer(
        PlayerEnabledTimerHandle,
        InputTimerDelegate,
        StartDelay,
        false);
  }
}