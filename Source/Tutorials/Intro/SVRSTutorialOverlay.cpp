// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

//#include "IntroTutorialsPrivatePCH.h"
//#include "STutorialOverlay.h"
//#include "STutorialContent.h"
//#include "EditorTutorial.h"
//#include "IntroTutorials.h"
//#include "Kismet2/KismetEditorUtilities.h"
//#include "LevelEditor.h"
//#include "BlueprintEditorUtils.h"
//#include "Guid.h"
//#include "BlueprintEditor.h"

#include "Tutorials.h"
#include "SVRSTutorialOverlay.h"
#include "SVRSTutorialContent.h"

static FName IntroTutorialsModuleName("IntroTutorials");



void SVRSTutorialOverlay::Construct(const FArguments& InArgs)
{
	ParentWindow = InArgs._ParentWindow;
	bIsStandalone = InArgs._IsStandalone;
	OnClosed = InArgs._OnClosed;
	//bHasValidContent = InStage != nullptr;
	//OnWidgetWasDrawn = InArgs._OnWidgetWasDrawn;

	TSharedPtr<SOverlay> Overlay;

	ChildSlot
	[
		SAssignNew(Overlay, SOverlay)
		+ SOverlay::Slot()
		[
			SAssignNew(OverlayCanvas, SCanvas)
		]
	];


	FVector2D Tmp(100, 100);
	FVector2D Tmp1(200, 200);

	OverlayCanvas->AddSlot()
		.Position(Tmp)
		.Size(Tmp1)
		[
			SNew(SButton)
		];



	//if (InStage != nullptr)
	//{
	//	// add non-widget content, if any
	//	if (InArgs._AllowNonWidgetContent && InStage->Content.Type != EVRSTutorialContent::None)
	//	{
	//		//Overlay->AddSlot()
	//		//[
	//		//	SNew(SHorizontalBox)
	//		//	+ SHorizontalBox::Slot()
	//		//	.VAlign(VAlign_Center)
	//		//	.HAlign(HAlign_Center)
	//		//	[
	//		//		SNew(SVRSTutorialContent, InTutorial, InStage->Content)
	//		//		.OnClosed(InArgs._OnClosed)
	//		//		.OnNextClicked(InArgs._OnNextClicked)
	//		//		.OnHomeClicked(InArgs._OnHomeClicked)
	//		//		.OnBackClicked(InArgs._OnBackClicked)
	//		//		.IsBackEnabled(InArgs._IsBackEnabled)
	//		//		.IsHomeEnabled(InArgs._IsHomeEnabled)
	//		//		.IsNextEnabled(InArgs._IsNextEnabled)
	//		//		.IsStandalone(InArgs._IsStandalone)
	//		//		.WrapTextAt(600.0f)
	//		//		.NextButtonText(InStage->NextButtonText)
	//		//		.BackButtonText(InStage->BackButtonText)
	//		//	]
	//		//];
	//	}

	//	if (InStage->WidgetContent.Num() > 0)
	//	{
	//		//FIntroTutorials& IntroTutorials = FModuleManager::Get().GetModuleChecked<FIntroTutorials>("IntroTutorials");

	//		// now add canvas slots for widget-bound content
	//		for (const FVRSTutorialWidgetContent& WidgetContent : InStage->WidgetContent)
	//		{
	//			if (WidgetContent.Content.Type != EVRSTutorialContent::None)
	//			{
	//				//TSharedPtr<SVRSTutorialContent> ContentWidget =
	//				//	SNew(SVRSTutorialContent, InTutorial, WidgetContent.Content)
	//				//	.HAlign(WidgetContent.HorizontalAlignment)
	//				//	.VAlign(WidgetContent.VerticalAlignment)
	//				//	.Offset(WidgetContent.Offset)
	//				//	.IsStandalone(bIsStandalone)
	//				//	.OnClosed(InArgs._OnClosed)
	//				//	.OnNextClicked(InArgs._OnNextClicked)
	//				//	.OnHomeClicked(InArgs._OnHomeClicked)
	//				//	.OnBackClicked(InArgs._OnBackClicked)
	//				//	.IsBackEnabled(InArgs._IsBackEnabled)
	//				//	.IsHomeEnabled(InArgs._IsHomeEnabled)
	//				//	.IsNextEnabled(InArgs._IsNextEnabled)
	//				//	.WrapTextAt(WidgetContent.ContentWidth)
	//				//	//.Anchor(WidgetContent.WidgetAnchor)
	//				//	.AllowNonWidgetContent(InArgs._AllowNonWidgetContent)
	//				//	.OnWasWidgetDrawn(InArgs._OnWasWidgetDrawn);

	//				//PerformWidgetInteractions(InTutorial, WidgetContent);

	//				//OverlayCanvas->AddSlot()
	//				//	.Position(TAttribute<FVector2D>::Create(TAttribute<FVector2D>::FGetter::CreateSP(ContentWidget.Get(), &SVRSTutorialContent::GetPosition)))
	//				//	.Size(TAttribute<FVector2D>::Create(TAttribute<FVector2D>::FGetter::CreateSP(ContentWidget.Get(), &SVRSTutorialContent::GetSize)))
	//				//	[
	//				//		ContentWidget.ToSharedRef()
	//				//	];



	//				//OnPaintNamedWidget.AddSP(ContentWidget.Get(), &SVRSTutorialContent::HandlePaintNamedWidget);
	//				//OnResetNamedWidget.AddSP(ContentWidget.Get(), &SVRSTutorialContent::HandleResetNamedWidget);
	//				//OnCacheWindowSize.AddSP(ContentWidget.Get(), &SVRSTutorialContent::HandleCacheWindowSize);
	//			}
	//		}
	//	}
	//}
}
