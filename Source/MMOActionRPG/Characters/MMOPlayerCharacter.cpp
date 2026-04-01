// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MMOPlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

AMMOPlayerCharacter::AMMOPlayerCharacter()
{
 	// Tick = false
	PrimaryActorTick.bCanEverTick = false;
	// 콜리전 캡슐 사이즈
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// 카메라 시점 따라가기
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 캐릭터 무브먼트 설정
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// 캐릭터 무브먼트 설정값
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// 카메라 & 카메라 붐 설정
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// FollowCamera 설정
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void AMMOPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (IsValid(EnhancedInputComponent) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' EnhancedInputComponent is nullptr"), *GetNameSafe(this))
		return;
	}
	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMMOPlayerCharacter::Move);
	EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMMOPlayerCharacter::Look);
}

void AMMOPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMMOPlayerCharacter::DoMove(float Right, float Forward)
{
	if (IsValid(GetController()) == false)
		return;
	
	const FRotator Rotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	AddMovementInput(ForwardDirection, Forward);
	AddMovementInput(RightDirection, Right);
}

void AMMOPlayerCharacter::DoLook(float Yaw, float Pitch)
{
	if (IsValid(GetController()) == false)
		return;
	
	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);
}

void AMMOPlayerCharacter::DoJumpStart()
{
	Jump();
}

void AMMOPlayerCharacter::DoJumpEnd()
{
	StopJumping();
}

void AMMOPlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	DoMove(MovementVector.X, MovementVector.Y);
}

void AMMOPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

