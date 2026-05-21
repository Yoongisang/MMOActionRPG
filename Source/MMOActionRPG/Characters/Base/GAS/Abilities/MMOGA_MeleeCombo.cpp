// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOGA_MeleeCombo.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Characters/Base/GAS/MMOGameplayTags.h"
#include "GameFramework/Character.h"
#include "UObject/ObjectKey.h"
#include "Animation/AnimInstance.h"

UMMOGA_MeleeCombo::UMMOGA_MeleeCombo()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	
	ComboSections = {
		TEXT("Combo1"),
		TEXT("Combo2"),
		TEXT("Combo3")
	};
}

void UMMOGA_MeleeCombo::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (IsValid(ComboMontage) == false || ComboSections.IsEmpty())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	if (CommitAbility(Handle, ActorInfo, ActivationInfo) == false)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	CurrentComboIndex = 0;
	bComboInputBuffered = false;
	bComboWindowOpened = false;
	
	BindGameplayEvents();
	StartCombo();
}

void UMMOGA_MeleeCombo::InputPressed(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, 
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	
	bComboInputBuffered = true;
	
	if (bComboWindowOpened)
	{
		TryAdvanceCombo();
	}
}

void UMMOGA_MeleeCombo::EndAbility(
	const FGameplayAbilitySpecHandle Handle, 
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, 
	bool bReplicateEndAbility, 
	bool bWasCancelled)
{
	MontageTask = nullptr;
	ComboWindowTask = nullptr;
	HitEventTask = nullptr;
	
	CurrentComboIndex = 0;
	bComboInputBuffered = false;
	bComboWindowOpened = false;
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMMOGA_MeleeCombo::HandleMontageCompleted()
{
	if (bEndAbilityOnMontageCompleted)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}

void UMMOGA_MeleeCombo::HandleMontageInterrupted()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UMMOGA_MeleeCombo::HandleMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UMMOGA_MeleeCombo::HandleComboWindow(FGameplayEventData Payload)
{
	bComboWindowOpened = true;
	
	if (bComboInputBuffered)
	{
		TryAdvanceCombo();
	}
}

void UMMOGA_MeleeCombo::HandleHitEvent(FGameplayEventData Payload)
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (IsValid(AvatarActor) == false || AvatarActor->HasAuthority() == false)
	{
		return;
	}
	
	ApplyDamageEffectToTargets(Payload.TargetData);
}

void UMMOGA_MeleeCombo::StartCombo()
{
	MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		NAME_None,
		ComboMontage,
		1.f,
		ComboSections[CurrentComboIndex],
		true
		);
	
	if (IsValid(MontageTask) == false)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}
	
	MontageTask->OnCompleted.AddUniqueDynamic(this, &UMMOGA_MeleeCombo::HandleMontageCompleted);
	MontageTask->OnInterrupted.AddUniqueDynamic(this, &UMMOGA_MeleeCombo::HandleMontageInterrupted);
	MontageTask->OnCancelled.AddUniqueDynamic(this, &UMMOGA_MeleeCombo::HandleMontageCancelled);
	MontageTask->ReadyForActivation();
}

void UMMOGA_MeleeCombo::TryAdvanceCombo()
{
	const int32 NextComboIndex = CurrentComboIndex + 1;
	if (ComboSections.IsValidIndex(NextComboIndex) == false)
	{
		return;
	}
	
	CurrentComboIndex = NextComboIndex;
	bComboInputBuffered = false;
	bComboWindowOpened = false;
	
	JumpToCurrentComboSection();
}

void UMMOGA_MeleeCombo::JumpToCurrentComboSection()
{
	ACharacter* Character = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	if (IsValid(Character) == false || IsValid(Character->GetMesh()) == false)
	{
		return;
	}
	
	UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance();
	if (IsValid(AnimInstance) == false || IsValid(ComboMontage) == false || ComboSections.IsValidIndex(CurrentComboIndex) == false)
	{
		return;
	}
	
	AnimInstance->Montage_JumpToSection(ComboSections[CurrentComboIndex], ComboMontage);
}

void UMMOGA_MeleeCombo::BindGameplayEvents()
{
	ComboWindowTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
		this,
		MMOGameplayTags::Combat_Window_Combo,
		nullptr,
		false,
		true
		);
	
	if (IsValid(ComboWindowTask))
	{
		ComboWindowTask->EventReceived.AddUniqueDynamic(this, &UMMOGA_MeleeCombo::HandleComboWindow);
		ComboWindowTask->ReadyForActivation();
	}
	
	HitEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
	this,
	MMOGameplayTags::Event_Hit,
	nullptr,
	false,
	true
	);
	
	if (IsValid(HitEventTask))
	{
		HitEventTask->EventReceived.AddUniqueDynamic(this, &UMMOGA_MeleeCombo::HandleHitEvent);
		HitEventTask->ReadyForActivation();
	}
}

void UMMOGA_MeleeCombo::ApplyDamageEffectToTargets(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (IsValid(DamageEffectClass) == false)
	{
		return;
	}
	
	UAbilitySystemComponent* SourceASC = GetAbilitySystemComponentFromActorInfo();
	if (IsValid(SourceASC) == false)
	{
		return;
	}
	
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (IsValid(AvatarActor) == false)
	{
		return;
	}
	
	const float ComboMultiplier = ComboDamageMultipliers.IsValidIndex(CurrentComboIndex)
		? ComboDamageMultipliers[CurrentComboIndex]
		: 1.f;
	
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, GetAbilityLevel());
	if (SpecHandle.IsValid() == false)
	{
		return;
	}
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(
	SpecHandle,
	MMOGameplayTags::Data_DamageMultiplier,
	ComboMultiplier);
	
	TSet<TObjectKey<AActor>> AppliedTargets;
	
	for (int32 DataIndex = 0; DataIndex < TargetDataHandle.Num(); DataIndex++)
	{
		const FGameplayAbilityTargetData* TargetData = TargetDataHandle.Get(DataIndex);
		if (!TargetData)
		{
			continue;
		}
		
		for (TWeakObjectPtr<AActor> TargetActor : TargetData->GetActors())
		{
			if (TargetActor.IsValid() == false || TargetActor.Get() == AvatarActor)
			{
				continue;
			}
			
			const TObjectKey<AActor> TargetKey(TargetActor.Get());
			if (AppliedTargets.Contains(TargetKey))
			{
				continue;
			}
			
			UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor.Get());
			if (IsValid(TargetASC) == false || TargetASC->HasMatchingGameplayTag(MMOGameplayTags::State_Dead))
			{
				continue;
			}
			SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
			AppliedTargets.Add(TargetKey);
		}
	}
}
