// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DistanceToolsEdMode.h"
#include "DistanceToolsEdModeToolkit.h"
#include "Toolkits/ToolkitManager.h"
#include "EditorModeManager.h"
#include "LevelEditor.h"
#include "SOverlay.h"
#include "SWidget.h"
#include "ILevelViewport.h"
#include "ModuleManager.h"
#include "EditorViewportClient.h"
#include "STextBlock.h"
#include "Engine/Selection.h"
#include "SBorder.h"

const FEditorModeID FDistanceToolsEdMode::EM_DistanceToolsEdModeId = TEXT("EM_DistanceToolsEdMode");

#define LOCTEXT_NAMESPACE "DistanceTools"

FDistanceToolsEdMode::FDistanceToolsEdMode()
{

}

FDistanceToolsEdMode::~FDistanceToolsEdMode()
{

}

void FDistanceToolsEdMode::Enter()
{
	FEdMode::Enter();

	if (!Toolkit.IsValid() && UsesToolkits())
	{
		Toolkit = MakeShareable(new FDistanceToolsEdModeToolkit);
		Toolkit->Init(Owner->GetToolkitHost());
	}

	FLevelEditorModule& LevelEditor = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	TSharedPtr<ILevelViewport> LViewport = LevelEditor.GetFirstActiveViewport();

	DistanceWidget->ClearChildren();

	DistanceWidget->AddSlot()
		.Padding(FMargin(40.0f, 40.0f, 40.0f, 40.0f))
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Left)
		[
			SAssignNew(DistanceTextBox, STextBlock)
			.ColorAndOpacity(FLinearColor::White)
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 14))
		];

	LViewport->AddOverlayWidget(DistanceWidget);
}

void FDistanceToolsEdMode::Tick(FEditorViewportClient* ViewportClient, float DeltaTime)
{
	FEdMode::Tick(ViewportClient, DeltaTime);
	UpdateCameraLocation(ViewportClient);

	//Make sure we actually have a selection
	if (GEditor->GetSelectedActorCount() <= 0) return;
	
	DistanceActor = GetSelected(ViewportClient);
	if (DistanceActor == nullptr) return;

	//Update our text!
	UpdateDistanceText();
}

void FDistanceToolsEdMode::Exit()
{
	if (Toolkit.IsValid())
	{
		FToolkitManager::Get().CloseToolkit(Toolkit.ToSharedRef());
		Toolkit.Reset();
	}
	
	FEdMode::Exit();
}

AActor* FDistanceToolsEdMode::GetSelected(FEditorViewportClient* ViewportClient)
{
	USelection* SelectedActors = GEditor->GetSelectedActors();
	TArray<AActor*> Actors;
	for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
	{
		AActor* Actor = Cast<AActor>(*Iter);
		if (Actor)
		{
			Actors.Add(Actor);
		}
	}

	return Actors[0];
}

void FDistanceToolsEdMode::UpdateCameraLocation(FEditorViewportClient* ViewportClient)
{
	//Set our Viewport to be real-time. May not be needed, but because we want to update, it's good practice.
	FSceneViewFamilyContext ViewFamily(FSceneViewFamily::ConstructionValues(
		ViewportClient->Viewport,
		ViewportClient->GetScene(),
		ViewportClient->EngineShowFlags)
		.SetRealtimeUpdate(ViewportClient->IsRealtime()));

	//Update Camera Location.
	CameraLocation = ViewportClient->GetViewLocation();
}

void FDistanceToolsEdMode::UpdateDistanceText()
{
	float DistanceToObject = (CameraLocation - DistanceActor->GetActorLocation()).Size();
	FFormatNamedArguments Arguments;
	Arguments.Add("ActorName", FText::FromName(DistanceActor->GetFName()));
	Arguments.Add("Distance", FText::AsNumber(DistanceToObject));
	DistanceTextBox->SetText(FText::Format(LOCTEXT("DistanceToActor", "[{ActorName}] {Distance}"), Arguments));
}

bool FDistanceToolsEdMode::UsesToolkits() const
{
	return true;
}

#undef LOCTEXT_NAMESPACE
