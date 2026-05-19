// Copyright Jakub Kaczor


#include "GASCrash/Public/Player/GC_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"

void AGC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem{ ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()) };
	if (!IsValid(InputSubsystem)) return;
	
	for (UInputMappingContext* Context : InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(Context, 0);
	}
	
	UEnhancedInputComponent* EIC{ Cast<UEnhancedInputComponent>(InputComponent) };
	if (!IsValid(EIC)) return;
	
	EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AGC_PlayerController::Jump);
	EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AGC_PlayerController::StopJumping);
	EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGC_PlayerController::Move);
	EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGC_PlayerController::Look);
	
	EIC->BindAction(PrimaryAction, ETriggerEvent::Started, this, &AGC_PlayerController::Primary);
}

void AGC_PlayerController::Jump()
{
	if (!IsValid(GetCharacter())) return;
	
	GetCharacter()->Jump();
}

void AGC_PlayerController::StopJumping()
{
	if (!IsValid(GetCharacter())) return;
	
	GetCharacter()->StopJumping();
}

void AGC_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn())) return;
	
	const FVector2D MovementVector{ Value.Get<FVector2D>() };
	
	// Find which way is forward
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection{ FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X) };
	const FVector RightDirection{ FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y) };
	
	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void AGC_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector{ Value.Get<FVector2D>() };
	
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AGC_PlayerController::Primary()
{
	
}
