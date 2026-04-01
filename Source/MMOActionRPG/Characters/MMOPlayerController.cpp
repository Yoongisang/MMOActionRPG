// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MMOPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

AMMOPlayerController::AMMOPlayerController()
{
}

void AMMOPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMMOPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (IsLocalController() == false)
		return;
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IsValid(Subsystem) == false)
		return;
	
	for (const UInputMappingContext* CurrentContext : DefaultMappingContexts)
	{
		Subsystem->AddMappingContext(CurrentContext, 0);
	}
}
