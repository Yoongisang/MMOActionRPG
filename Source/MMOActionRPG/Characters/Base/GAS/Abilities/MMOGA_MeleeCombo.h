// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MMOGA_MeleeCombo.generated.h"

class UAnimMontage;
class UGameplayEffect;
class UAbilityTask_PlayMontageAndWait;
class UAbilityTask_WaitGameplayEvent;

/**
 * 
 */
UCLASS()
class MMOACTIONRPG_API UMMOGA_MeleeCombo : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UMMOGA_MeleeCombo();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData) override;
	
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateEndAbility, 
		bool bWasCancelled) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
	TObjectPtr<UAnimMontage> ComboMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
	TArray<FName> ComboSections;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combo")
	bool bEndAbilityOnMontageCompleted = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	// AttributeSet에서 공격력 받아와서 데미지 배율로 콤보 단계별 데미지 설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TArray<float> ComboDamageMultipliers = { 1.f, 1.2f, 1.5f };
	
private:
	UFUNCTION()
	void HandleMontageCompleted();

	UFUNCTION()
	void HandleMontageInterrupted();

	UFUNCTION()
	void HandleMontageCancelled();

	UFUNCTION()
	void HandleComboWindow(FGameplayEventData Payload);

	UFUNCTION()
	void HandleHitEvent(FGameplayEventData Payload);

	void StartCombo();
	void TryAdvanceCombo();
	void JumpToCurrentComboSection();
	void BindGameplayEvents();
	void ApplyDamageEffectToTargets(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	int32 CurrentComboIndex = 0;
	bool bComboInputBuffered = false;
	bool bComboWindowOpened = false;

	UPROPERTY()
	TObjectPtr<UAbilityTask_PlayMontageAndWait> MontageTask;

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitGameplayEvent> ComboWindowTask;

	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitGameplayEvent> HitEventTask;
};
