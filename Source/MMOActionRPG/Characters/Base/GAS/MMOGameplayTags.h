// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace MMOGameplayTags
{
    // State.Common - 플레이어/몬스터 공통 상태
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Dead)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Stunned)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Stop)

    // State.Player - 플레이어 전용 상태
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Invincible)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_CannotCanceled)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Unstoppable)

    // State.Monster - 몬스터 전용 상태
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Monster_Invincible)

    // Ability.Player - 플레이어 어빌리티 실행 중
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Attack_Melee)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Dodge)

    // Ability.Monster - 몬스터 어빌리티 실행 중
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Monster_Attack)

    // CoolDown
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(CoolDown_Player_Dodge)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(CoolDown_Player_Attack_Melee)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(CoolDown_Monster_Attack)

    // Combat - 플레이어 전투 윈도우
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Combat_Window_Combo)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Combat_Window_Parry)

    // Effect - 공통 버프/디버프
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Debuff_Slow)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Debuff_Stun)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Buff_AttackUp)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Effect_Buff_Shield)

    // Event - AnimNotify / GameplayEvent 공통
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Hit)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Death)

    // Data - SetByCaller 공통
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_Damage)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_CoolTime)
    UE_DECLARE_GAMEPLAY_TAG_EXTERN(Data_DebuffTime)
}