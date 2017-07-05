// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tutorials : ModuleRules
{
	public Tutorials(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(
            new string[] {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "HeadMountedDisplay",
                "UMG",
                "RenderCore",
                "RHI",
                "Slate",
                "SlateCore",
                "RHI"
            });

        PublicIncludePaths.AddRange(
            new string[]
            {
                //"UMG/Public/Components",
                "Tutorials/Intro"
            });
	}
}
