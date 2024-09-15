#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

class ATank;
class ATankController;

UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor *DeadActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void GameOver(bool bWonGame);

private:
	ATank *Tank;
	ATankController *TankController;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay", meta = (AllowPrivateAccess = "true"))
	float StartDelay = 4.f;

	void HandleGameStart();

	int32 TargetTowers = 0;
	const int32 GetTargetTowersCount();
};
