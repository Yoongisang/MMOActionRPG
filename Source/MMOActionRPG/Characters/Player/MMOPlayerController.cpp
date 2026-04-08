// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/MMOPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

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
	
	for (int32 i = 0; i <DefaultMappingContexts.Num(); i++)
	{
		Subsystem->AddMappingContext(DefaultMappingContexts[i], i);
	}
}
