// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VR_Survival : ModuleRules
{
	public VR_Survival(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
            "Niagara",
            "AIModule",
            "NavigationSystem",
            "GameplayTasks"
        });
	}
}
