// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DistanceTools.h"
#include "DistanceToolsEdMode.h"
#include "Editor.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FDistanceToolsModule"

void FDistanceToolsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FEditorModeRegistry::Get().RegisterMode<FDistanceToolsEdMode>(FDistanceToolsEdMode::EM_DistanceToolsEdModeId, LOCTEXT("DistanceToolsEdModeName", "DistanceToolsEdMode"), FSlateIcon(), true);
	//GLevelEditorModeTools().ActivateMode(FDistanceToolsEdMode::EM_DistanceToolsEdModeId);
}

void FDistanceToolsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorModeRegistry::Get().UnregisterMode(FDistanceToolsEdMode::EM_DistanceToolsEdModeId);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDistanceToolsModule, DistanceTools)