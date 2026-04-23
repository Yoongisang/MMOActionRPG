// Fill out your copyright notice in the Description page of Project Settings.


#include "MMOGameplayTags.h"

namespace MMOGameplayTags
{
    // State.Common
    UE_DEFINE_GAMEPLAY_TAG(State_Dead,    "State.Dead")
    UE_DEFINE_GAMEPLAY_TAG(State_Stunned, "State.Stunned")
    UE_DEFINE_GAMEPLAY_TAG(State_Stop,    "State.Stop")


    // State.Player
    UE_DEFINE_GAMEPLAY_TAG(State_Player_Invincible,     "State.Player.Invincible")
    UE_DEFINE_GAMEPLAY_TAG(State_Player_CannotCanceled, "State.Player.CannotCanceled")
    UE_DEFINE_GAMEPLAY_TAG(State_Player_Unstoppable,    "State.Player.Unstoppable")
    
    // State.Monster
    UE_DEFINE_GAMEPLAY_TAG(State_Monster_Invincible, "State.Monster.Invincible")
    
    // Ability.Player
    UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Attack_Melee, "Ability.Player.Attack.Melee")
    UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Dodge,        "Ability.Player.Dodge")
    
    // Ability.Monster
    UE_DEFINE_GAMEPLAY_TAG(Ability_Monster_Attack, "Ability.Monster.Attack")

    // CoolDown
    UE_DEFINE_GAMEPLAY_TAG(CoolDown_Player_Dodge,        "CoolDown.Player.Dodge")
    UE_DEFINE_GAMEPLAY_TAG(CoolDown_Player_Attack_Melee, "CoolDown.Player.Attack.Melee")
    UE_DEFINE_GAMEPLAY_TAG(CoolDown_Monster_Attack,      "CoolDown.Monster.Attack")
    
    // Combat
    UE_DEFINE_GAMEPLAY_TAG(Combat_Window_Combo, "Combat.Window.Combo")
    UE_DEFINE_GAMEPLAY_TAG(Combat_Window_Parry, "Combat.Window.Parry")
    
    // Effect
    UE_DEFINE_GAMEPLAY_TAG(Effect_Debuff_Slow,   "Effect.Debuff.Slow")
    UE_DEFINE_GAMEPLAY_TAG(Effect_Debuff_Stun,   "Effect.Debuff.Stun")
    UE_DEFINE_GAMEPLAY_TAG(Effect_Buff_AttackUp, "Effect.Buff.AttackUp")
    UE_DEFINE_GAMEPLAY_TAG(Effect_Buff_Shield,   "Effect.Buff.Shield")
    
    // Event
    UE_DEFINE_GAMEPLAY_TAG(Event_Hit,   "Event.Hit")
    UE_DEFINE_GAMEPLAY_TAG(Event_Death, "Event.Death")

    // Data
    UE_DEFINE_GAMEPLAY_TAG(Data_Damage,     "Data.Damage")
    UE_DEFINE_GAMEPLAY_TAG(Data_CoolTime,   "Data.CoolTime")
    UE_DEFINE_GAMEPLAY_TAG(Data_DebuffTime, "Data.DebuffTime")
}