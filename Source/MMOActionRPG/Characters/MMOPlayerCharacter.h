// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MMOCharacterBase.h"
#include "MMOPlayerCharacter.generated.h"

UCLASS()
class MMOACTIONRPG_API AMMOPlayerCharacter : public AMMOCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMMOPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
