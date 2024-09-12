// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class TOONTANKS_API ATankController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext *InputMappingContext;

protected:
	virtual void BeginPlay() override;
};
