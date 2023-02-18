// Copyright (c) Tolgee. All Rights Reserved.

using UnrealBuildTool;

public class Tolgee : ModuleRules
{
    public Tolgee(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", 
                "HTTP",
                "Json",
                "JsonUtilities",
                "DeveloperSettings"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
            }
        );
    }
}
