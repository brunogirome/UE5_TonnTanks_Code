#include "ToonTanksGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "Tank.h"
#include "Tower.h"

void AToonTanksGameMode::ActorDied(AActor *DeadActor)
{
  if (Tank && DeadActor == Tank)
  {
    Tank->HandleDestruction();
    if (Tank->GetTankPlayerController())
    {
      Tank->DisableInput(Tank->GetTankPlayerController());
      Tank->GetTankPlayerController()->bShowMouseCursor = false;
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
}