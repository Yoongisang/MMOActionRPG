// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOBaseAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UMMOBaseAttributeSet::OnRep_HP(const FGameplayAttributeData& OldHP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOBaseAttributeSet, HP, OldHP);
}

void UMMOBaseAttributeSet::OnRep_MP(const FGameplayAttributeData& OldMP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOBaseAttributeSet, MP, OldMP);
}

void UMMOBaseAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOBaseAttributeSet, MaxHP, OldMaxHP);
}

void UMMOBaseAttributeSet::OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMMOBaseAttributeSet, MaxMP, OldMaxMP);
}

void UMMOBaseAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMMOBaseAttributeSet, HP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMMOBaseAttributeSet, MaxHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMMOBaseAttributeSet, MP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMMOBaseAttributeSet, MaxMP, COND_None, REPNOTIFY_Always);
}
