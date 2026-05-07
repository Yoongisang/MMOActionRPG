// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_MeleeHitTrace.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Characters/Base/GAS/MMOGameplayTags.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

void UAnimNotify_MeleeHitTrace::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;
	if (!Owner || !Owner->GetWorld()) return;

	// 소켓 위치 기준으로 구체 오버랩
	const FVector TraceCenter = MeshComp->GetSocketLocation(TraceSocketName);

	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	Owner->GetWorld()->OverlapMultiByChannel(
		Overlaps,
		TraceCenter,
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeSphere(TraceRadius),
		Params);


	if (bDrawDebug)
	{
		DrawDebugSphere(Owner->GetWorld(), TraceCenter, TraceRadius, 12,
			FColor::Red, false, 1.f);
	}
	
	if (Overlaps.IsEmpty()) return;

	// 감지된 액터를 TargetData로 포장
	FGameplayAbilityTargetData_ActorArray* TargetData =
		new FGameplayAbilityTargetData_ActorArray();

	for (const FOverlapResult& Overlap : Overlaps)
	{
		AActor* HitActor = Overlap.GetActor();
		if (HitActor && HitActor->ActorHasTag(TEXT("Enemy")))
		{
			TargetData->TargetActorArray.Add(HitActor);
		}
	}

	if (TargetData->TargetActorArray.IsEmpty())
	{
		delete TargetData;
		return;
	}

	// TargetData를 이벤트 페이로드에 담아 ASC로 전송
	FGameplayEventData Payload;
	Payload.TargetData = FGameplayAbilityTargetDataHandle(TargetData);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		Owner, MMOGameplayTags::Event_Hit, Payload);
}
