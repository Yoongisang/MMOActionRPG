// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MMOBaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class MMOACTIONRPG_API UMMOBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnRep_HP(const FGameplayAttributeData& OldHP);
	
	UFUNCTION()
	void OnRep_MP(const FGameplayAttributeData& OldMP);
	
	UFUNCTION()
	void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP);
	
	UFUNCTION()
	void OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP);
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	// GE가 계산한 값을 AttributeSet에 반영하기 직전에 호출
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// GE가 AttributeSet에 완전히 반영된 후 호출 바뀐 결과를 보고 후처리
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_HP)
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UMMOBaseAttributeSet, HP)
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxHP)
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UMMOBaseAttributeSet, MaxHP)
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MP)
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UMMOBaseAttributeSet, MP)
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", ReplicatedUsing = OnRep_MaxMP)
	FGameplayAttributeData MaxMP;
	ATTRIBUTE_ACCESSORS(UMMOBaseAttributeSet, MaxMP)
};
