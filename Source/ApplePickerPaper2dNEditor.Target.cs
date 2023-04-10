// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class ApplePickerPaper2dNEditorTarget : TargetRules
{
	public ApplePickerPaper2dNEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("ApplePickerPaper2dN");
	}
}
