// Copyright 2023 JesseTheCatLover. All Rights Reserved.


#include "ShooterAnimInstance.h"
#include "ShooterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if(ShooterCharacter == nullptr)
	{
		ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
	}

	if(ShooterCharacter)
	{
		// Getting the lateral speed of the character from velocity
		FVector Velocity = { ShooterCharacter -> GetVelocity() };
		Velocity.Z = 0;
		speed = Velocity.Size();

		// Is the character in the air?
		bIsInAir = ShooterCharacter -> GetCharacterMovement() -> IsFalling();

		// Is the character accelerating?
		if(ShooterCharacter -> GetCharacterMovement() -> GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		// Calculating MovementOffsetYaw for strafing
		FRotator AimRotation = ShooterCharacter -> GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter -> GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if(ShooterCharacter -> GetVelocity().Size() > 0.f)
		{
			LastMovementOffsetYaw = MovementOffsetYaw;
		}

		bAiming = ShooterCharacter -> GetAiming();
	}
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}



