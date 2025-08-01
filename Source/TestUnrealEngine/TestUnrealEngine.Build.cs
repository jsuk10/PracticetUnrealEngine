// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestUnrealEngine : ModuleRules
{
	public TestUnrealEngine(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		//UMG추가 안하면 오류 나는 경우 생김.
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG","AIModule" ,"GameplayTasks" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
