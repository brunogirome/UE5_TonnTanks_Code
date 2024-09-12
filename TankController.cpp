// Fill out your copyright notice in the Description page of Project Settings.

#include "TankController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void ATankController::BeginPlay()
{
  Super::BeginPlay();

  if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
  {
    Subsystem->AddMappingContext(InputMappingContext, 0);
  }
}