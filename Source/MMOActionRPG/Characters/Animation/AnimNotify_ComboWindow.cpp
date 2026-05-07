// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_ComboWindow.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/Base/GAS/MMOGameplayTags.h"

void UAnimNotify_ComboWindow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;
	if (Owner == nullptr) 
		return;

	FGameplayEventData Payload;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		Owner, MMOGameplayTags::Combat_Window_Combo, Payload);
}
