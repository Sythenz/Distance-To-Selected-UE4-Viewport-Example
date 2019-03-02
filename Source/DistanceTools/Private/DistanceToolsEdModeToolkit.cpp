// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "DistanceToolsEdModeToolkit.h"
#include "DistanceToolsEdMode.h"
#include "Engine/Selection.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "FDistanceToolsEdModeToolkit"

FDistanceToolsEdModeToolkit::FDistanceToolsEdModeToolkit()
{
}

void FDistanceToolsEdModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost)
{
	//struct Locals
	//{
	//	static bool IsWidgetEnabled()
	//	{
	//		return GEditor->GetSelectedActors()->Num() != 0;
	//	}

	//	static FReply OnButtonClick(FVector InOffset)
	//	{
	//		USelection* SelectedActors = GEditor->GetSelectedActors();

	//		// Let editor know that we're about to do something that we want to undo/redo
	//		GEditor->BeginTransaction(LOCTEXT("MoveActorsTransactionName", "MoveActors"));

	//		// For each selected actor
	//		for (FSelectionIterator Iter(*SelectedActors); Iter; ++Iter)
	//		{
	//			if (AActor* LevelActor = Cast<AActor>(*Iter))
	//			{
	//				// Register actor in opened transaction (undo/redo)
	//				LevelActor->Modify();
	//				// Move actor to given location
	//				LevelActor->TeleportTo(LevelActor->GetActorLocation() + InOffset, FRotator(0, 0, 0));
	//			}
	//		}

	//		// We're done moving actors so close transaction
	//		GEditor->EndTransaction();

	//		return FReply::Handled();
	//	}

	//	static TSharedRef<SWidget> MakeButton(FText InLabel, const FVector InOffset)
	//	{
	//		return SNew(SButton)
	//			.Text(InLabel)
	//			.OnClicked_Static(&Locals::OnButtonClick, InOffset);
	//	}
	//};

	//const float Factor = 256.0f;		
	//FModeToolkit::Init(InitToolkitHost);
}

FName FDistanceToolsEdModeToolkit::GetToolkitFName() const
{
	return FName("DistanceToolsEdMode");
}

FText FDistanceToolsEdModeToolkit::GetBaseToolkitName() const
{
	return NSLOCTEXT("DistanceToolsEdModeToolkit", "DisplayName", "DistanceToolsEdMode Tool");
}

class FEdMode* FDistanceToolsEdModeToolkit::GetEditorMode() const
{
	return GLevelEditorModeTools().GetActiveMode(FDistanceToolsEdMode::EM_DistanceToolsEdModeId);
}

#undef LOCTEXT_NAMESPACE
