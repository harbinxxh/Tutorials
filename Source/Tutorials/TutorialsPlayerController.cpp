// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "TutorialsPlayerController.h"
#include "SVRSTutorialButton.h"
#include "SVRSTutorialRoot.h"
#include "SVRSTutorialOverlay.h"
#include "VRSEditorStyleSet.h"
#include "UMG.h"
#include "VRSTutorialContentMgr.h"
#include "VRSWidgetTutorialContentPanel.h"
#include "VRSTutorialWindow.h"

#include "SCustomWidget.h"

void ATutorialsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GTutorialWindow->Init();

	TSharedRef<SVerticalBox> Widget = SNew(SVerticalBox)
	+ SVerticalBox::Slot()
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	[
		SNew(SButton)
		.OnClicked(FOnClicked::CreateUObject(this, &ATutorialsPlayerController::ShowTutorial))
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("显示新手引导")))
		]
	]
	+ SVerticalBox::Slot()
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	[
		SNew(SButton)
		.OnClicked(FOnClicked::CreateUObject(this, &ATutorialsPlayerController::HideTutorial))
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("隐藏新手引导")))
		]
	]
	+ SVerticalBox::Slot()
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	[
		SNew(SButton)
		.OnClicked(FOnClicked::CreateUObject(this, &ATutorialsPlayerController::SetBorderPulsePosition))
		.Content()
		[
			SNew(STextBlock)
			.Text(FText::FromString(TEXT("设置PulsePosition")))
		]
	]
	+ SVerticalBox::Slot()
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	[
		SNew(SCustomWidget, ECustomWidget::CWS_TextBlock)
		.Text(FText::FromString(TEXT("文字描述")))
		//SNew(SButton)
	];

	GEngine->GameViewport->AddViewportWidgetForPlayer(GetLocalPlayer(), Widget, 1);
	/////////////////////////////////////////////////////

	//TutorialContent = SNew(SVRSTutorialContent);

	//Super::BeginPlay();
	//TSharedRef<SVerticalBox> widget = SNew(SVerticalBox)
	//+ SVerticalBox::Slot()
	//.Padding(10.f, 10.f, 10.f, 10.f)
	//.HAlign(HAlign_Right)
	//.VAlign(VAlign_Top)
	//[
	//	SNew(STutorialButton)
	//	.Context(TEXT("Test Button"))
	//	.ContextWindow(nullptr)
	//]
	//+ SVerticalBox::Slot()
	//.HAlign(HAlign_Center)
	//.VAlign(VAlign_Center)
	//[
	//	TutorialContent->AsShared()
	//];

	//GEngine->GameViewport->AddViewportWidgetForPlayer(GetLocalPlayer(), widget, 1);

	/////////////////////////////////////////////////////////////

	//GTutorialContentMgr->Init();

	//UVRSWidgetTutorialContentPanel* UserWidget = nullptr;
	//TSubclassOf<UVRSWidgetTutorialContentPanel> WidgetClass = LoadClass<UVRSWidgetTutorialContentPanel>(this, TEXT("/Game/BP/NewWidgetBlueprint.NewWidgetBlueprint_C"));
	//if (WidgetClass)
	//{
	//	UserWidget = CreateWidget<UVRSWidgetTutorialContentPanel>(GetWorld(), WidgetClass);
	//}
	//GTutorialContentMgr->TutorialContentPanel = UserWidget;

	//if (!UserWidget)
	//{
	//	return;
	//}

	//TSharedPtr<SOverlay> Overlay;


	//FVRSEditorStyle::ResetToDefault();
	//FGeometry Geom = FGeometry(FVector2D(12.f, 12.f), FVector2D(10.f, 76.f), FVector2D(311.f, 412.f), 1.f);

	//TSharedRef<SWindow> MainWindow = SNew(SWindow)
	//	.Title(FText::FromString(TEXT("MainWindow")))
	//	.SizingRule(ESizingRule::UserSized)
	//	.ClientSize(FVector2D(800, 600))
	//	.AutoCenter(EAutoCenter::PreferredWorkArea)
	//	.SupportsMinimize(false)
	//	[
	//		

	//	//	ChildSlot
	//	//	[
	//	//		SAssignNew(Overlay, SOverlay)
	//	//		+ SOverlay::Slot()
	//	//[
	//	//	SAssignNew(OverlayCanvas, SCanvas)
	//	//]
	//	//	];

	//		//SNew(SVRSTutorialOverlay)

	//		SNew(SVerticalBox)
	//		+ SVerticalBox::Slot()
	//	.HAlign(HAlign_Center)
	//	.VAlign(VAlign_Center)
	//	[
	//		SAssignNew(GTutorialContentMgr->VRSTutorialContent, SVRSTutorialContent, Geom)
	//	]
	//];
	//FSlateApplication::Get().AddWindow(MainWindow);

	////GTutorialContentMgr->VRSTutorialContent->SetVisibility(EVisibility::Hidden);
}

FReply ATutorialsPlayerController::ShowTutorial()
{
	GTutorialWindow->ShowTutorial(true);
	GTutorialWindow->ShowBorderPulse(true);
	return FReply::Handled();
}

FReply ATutorialsPlayerController::HideTutorial()
{
	GTutorialWindow->ShowTutorial(false);
	GTutorialWindow->ShowBorderPulse(false);
	return FReply::Handled();
}

FReply ATutorialsPlayerController::SetBorderPulsePosition()
{

	FGeometry Geom = FGeometry(FVector2D(100.f, 12.f), FVector2D(10.f, 76.f), FVector2D(311.f, 412.f), 1.f);
	GTutorialWindow->SetBorderPulseAnimation(Geom);
	return FReply::Handled();
}
