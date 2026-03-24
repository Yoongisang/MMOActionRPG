// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MMOCharacterBase.h"

// Sets default values
AMMOCharacterBase::AMMOCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMMOCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMMOCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMMOCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

