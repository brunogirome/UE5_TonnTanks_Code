#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ATank::ATank()
{
  SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
  SpringArmComponent->SetupAttachment(RootComponent);

  CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
  CameraComponent->SetupAttachment(SpringArmComponent);
}
