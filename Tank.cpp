#include "Tank.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/HitResult.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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
    EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
  }
}

void ATank::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  FHitResult hitResult;
  if (
      TankPlayerController &&
      GetWorld() &&
      TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult))
  {
    // UKismetSystemLibrary::DrawDebugSphere(GetWorld(), hitResult.Location, 30.f, 12, FColor::Red, 0.f, 1.f);
    RotateTurret(hitResult.Location);
  }
}

void ATank::HandleDestruction()
{
  Super::HandleDestruction();

  SetActorHiddenInGame(true);
  SetActorTickEnabled(false);

  // Destroy();
}

void ATank::BeginPlay()
{
  Super::BeginPlay();

  if (APlayerController *currentController = Cast<APlayerController>(GetController()))
  {
    TankPlayerController = currentController;
  }
}

void ATank::Move(const FInputActionValue &Value)
{
  float deltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
  FVector DeltaLocation = FVector();
  DeltaLocation.X = Value.Get<float>() * Speed * deltaSeconds;
  AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(const FInputActionValue &Value)
{
  float deltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
  FRotator DeltaRotation = FRotator();
  DeltaRotation.Yaw = Value.Get<float>() * TurnRate * deltaSeconds;
  AddActorLocalRotation(DeltaRotation, true);
}
