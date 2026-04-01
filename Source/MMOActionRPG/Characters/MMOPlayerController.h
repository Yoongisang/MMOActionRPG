// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MMOPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class MMOACTIONRPG_API AMMOPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMMOPlayerController();
	virtual void BeginPlay() override;
protected:
	virtual void SetupInputComponent() override;
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;
};
