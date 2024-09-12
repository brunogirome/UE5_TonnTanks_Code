#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputComponent;
class UInputAction;

struct FInputActionValue;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *RotateAction;

public:
	ATank();

	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent *SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent *CameraComponent;

	void Move(const FInputActionValue &Value);

	void Turn(const FInputActionValue &Value);
};
