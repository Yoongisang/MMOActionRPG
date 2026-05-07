// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_MeleeHitTrace.generated.h"

/**
 * 
 */
UCLASS()
class MMOACTIONRPG_API UAnimNotify_MeleeHitTrace : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference) override;
	
	// 몽타주에서 소켓 이름 지정 (예: "hand_r", "weapon_tip")
	UPROPERTY(EditAnywhere, Category = "Trace")
	FName TraceSocketName = TEXT("hand_r");

	// 구체 트레이스 반경 (cm)
	UPROPERTY(EditAnywhere, Category = "Trace")
	float TraceRadius = 50.f;

	// 트레이스 대상 채널
	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Pawn;
	
	// 에디터에서 트레이스 범위 시각화
	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDrawDebug = false;
};
