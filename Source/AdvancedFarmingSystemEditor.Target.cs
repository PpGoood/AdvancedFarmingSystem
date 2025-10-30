using UnrealBuildTool;
using System.Collections.Generic;

public class AdvancedFarmingSystemEditorTarget : TargetRules
{
	public AdvancedFarmingSystemEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		// 升级 BuildSettings
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "AdvancedFarmingSystem" } );
	}
}