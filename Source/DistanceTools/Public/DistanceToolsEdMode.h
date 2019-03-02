// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdMode.h"
#include "STextBlock.h"

class FDistanceToolsEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_DistanceToolsEdModeId;
public:
	FDistanceToolsEdMode();
	virtual ~FDistanceToolsEdMode();

	FVector CameraLocation;
	AActor* DistanceActor;

	/*
		We store a reference to our text box so we can dynamically update it later,
		rather than redrawing a new text box each time.
	*/
	TSharedPtr<STextBlock>	DistanceTextBox;

	// FEdMode interface
	virtual void Enter() override;
	virtual void Exit() override;

	/*
		Returns the first selected Actor.
		@param FEditorViewportClient* ViewportClient

		return AActor*
	*/
	AActor* GetSelected(FEditorViewportClient* ViewportClient);
	
	/*
		Gets our viewport's camera and updates the location.
		@param FEditorViewportClient* ViewportClient
		
		return void
	*/
	void UpdateCameraLocation(FEditorViewportClient* ViewportClient);
	

	/*
		Updates our text to the format of [ActorName] distance

		return void
	*/
	void UpdateDistanceText();

	virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;

	//virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;
	//virtual void ActorSelectionChangeNotify() override;
	bool UsesToolkits() const override;
	// End of FEdMode interface
};
