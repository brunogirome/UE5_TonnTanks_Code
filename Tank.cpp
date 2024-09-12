#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ATank::ATank()
{
  SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
  SpringArmComponent->SetupAttachment(RootComponent);

  CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
  {
    EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
    EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::Turn);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
  }
}

void ATank::Move(const FInputActionValue &Value)
{
  FVector newLocation = GetActorLocation() + GetActorForwardVector() * Value.Get<float>() * 20.f;
  SetActorLocation(newLocation);
}

void ATank::Turn(const FInputActionValue &Value)
{
  FRotator newRotation = GetActorRotation() + FRotator(0, Value.Get<float>(), 0);
  SetActorRotation(newRotation);
}