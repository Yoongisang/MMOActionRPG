// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MMOActionRPG : ModuleRules
{
	public MMOActionRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MMOActionRPG",
			"MMOActionRPG/Variant_Platforming",
			"MMOActionRPG/Variant_Platforming/Animation",
			"MMOActionRPG/Variant_Combat",
			"MMOActionRPG/Variant_Combat/AI",
			"MMOActionRPG/Variant_Combat/Animation",
			"MMOActionRPG/Variant_Combat/Gameplay",
			"MMOActionRPG/Variant_Combat/Interfaces",
			"MMOActionRPG/Variant_Combat/UI",
			"MMOActionRPG/Variant_SideScrolling",
			"MMOActionRPG/Variant_SideScrolling/AI",
			"MMOActionRPG/Variant_SideScrolling/Gameplay",
			"MMOActionRPG/Variant_SideScrolling/Interfaces",
			"MMOActionRPG/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
