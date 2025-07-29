// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestEditor : ModuleRules
{
    public TestEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[] {
                "Slate",
                "SlateCore",
                "EditorStyle",
                "UnrealEd",
                "Core",
                "CoreUObject",
                "Engine",
                "UnrealEd"
            }
        );

        PrivateIncludePaths.Add("TestEditor/Private");
    }
}