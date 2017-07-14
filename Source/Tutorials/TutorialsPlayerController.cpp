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


// �Ż�slate��ʽ�����ʽ
#include "SCustomWidget.h"


// ���� SDetailWidget �ؼ�
#include "SDetailWidget.h"



void ATutorialsPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TestSpinBoxValue = 0;
	TestCheckBoxState = ECheckBoxState::Checked;
	TestColor = FLinearColor::Red;

	GTutorialWindow->Init();

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	// ����ҳ�����ò�ͬ�Ŀؼ�
	// ���� SDetailWidget �ؼ�

	FDetailBuilder DetailBuilder;
	DetailBuilder.AddEntryBlock(
		TEXT("Check1"),
		EWidgetType::WT_TEXTBLOCK_CHECK,
		FText::FromString(TEXT("�����ռ���")),
		FOnCheckStateChanged::CreateUObject(this, &ATutorialsPlayerController::OnCheckStateChangedEvent)
	);

	DetailBuilder.AddEntryBlock(
		TEXT("Check2"),
		EWidgetType::WT_TEXTBLOCK_CHECK,
		FText::FromString(TEXT("�����߽���")),
		FOnCheckStateChanged::CreateUObject(this, &ATutorialsPlayerController::OnCheckStateChangedEvent)
	);

	DetailBuilder.AddEntryBlock(
		TEXT("Check3"),
		EWidgetType::WT_TEXTBLOCK_CHECK,
		FText::FromString(TEXT("���ɶ�����")),
		FOnCheckStateChanged::CreateUObject(this, &ATutorialsPlayerController::OnCheckStateChangedEvent)
	);

	// Combo
	TArray< TSharedPtr< FString > > RoomComboList;
	RoomComboList.Add(MakeShareable(new FString(TEXT("����"))));
	RoomComboList.Add(MakeShareable(new FString(TEXT("����"))));
	RoomComboList.Add(MakeShareable(new FString(TEXT("��ͯ��"))));
	RoomComboList.Add(MakeShareable(new FString(TEXT("�鷿"))));
	RoomComboList.Add(MakeShareable(new FString(TEXT("����"))));

	DetailBuilder.AddEntryBlock(
		TEXT("Combo1"),
		EWidgetType::WT_TEXTBLOCK_COMBO,
		FText::FromString(TEXT("�����ռ���")),
		RoomComboList,
		FOnComboBoxSelectionChanged::CreateUObject(this, &ATutorialsPlayerController::OnComboBoxSelectionChanged)
	);

	// Button
	DetailBuilder.AddEntryBlock(
		TEXT("Button1"),
		EWidgetType::WT_BUTTON,
		FText::FromString(TEXT("�ָ�Ĭ��ֵ")),
		FSimpleDelegate::CreateUObject(this, &ATutorialsPlayerController::OnButtonClicked)
	);

	TSharedRef<SWidget> DetailWidget = DetailBuilder.MakeWidget();


	TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox)
	+ SVerticalBox::Slot()
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Center)
	[
		DetailWidget
	];

	TSharedRef<SDetailWidget> StaticSDW = StaticCastSharedRef<SDetailWidget>(DetailWidget);
	TSharedPtr< SWidget > TempAA = StaticSDW->GetEntryBlockSWidget(TEXT("Check1"));
	TempAA->SetEnabled(false);

	GEngine->GameViewport->AddViewportWidgetForPlayer(GetLocalPlayer(), VerticalBox, 1);

	// ���� SDetailWidget �ؼ�
	// ����ҳ�����ò�ͬ�Ŀؼ�
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////




	/////////////////////////////////////////////////////////////////
	// �Ż�slate��ʽ�����ʽ

	//TSharedRef<SVerticalBox> VerticalBox = SNew(SVerticalBox)
	//+ SVerticalBox::Slot()
	//.HAlign(HAlign_Center)
	//.VAlign(VAlign_Center)
	//[
	//	SNew(SVerticalBox)
	//	+ SVerticalBox::Slot()
	//	[
	//		SNew(SBox)
	//		.Padding(2.f)
	//		[
	//			SNew(SButton)
	//			.OnClicked(FOnClicked::CreateUObject(this, &ATutorialsPlayerController::ShowTutorial))
	//			.Content()
	//			[
	//				SNew(STextBlock)
	//				.Text(FText::FromString(TEXT("��ʾ��������")))
	//			]
	//		]
	//	]
	//	+ SVerticalBox::Slot()
	//	[
	//		SNew(SBox)
	//		.Padding(2.f)
	//		[
	//			SNew(SButton)
	//			.OnClicked(FOnClicked::CreateUObject(this, &ATutorialsPlayerController::HideTutorial))
	//			.Content()
	//			[
	//				SNew(STextBlock)
	//				.Text(FText::FromString(TEXT("������������")))
	//			]
	//		]
	//	]
	//	+ SVerticalBox::Slot()
	//	[
	//		//SNew(SBox)
	//		//.Padding(2.f)
	//		//[
	//			SNew(SButton)
	//			.OnClicked(FOnClicked::CreateUObject(this, &ATutorialsPlayerController::SetBorderPulsePosition))
	//			.Content()
	//			[
	//				SNew(STextBlock)
	//				.Text(FText::FromString(TEXT("����PulsePosition")))
	//			]
	//		//]
	//	]
	//	+ SVerticalBox::Slot()
	//		.AutoHeight()
	//		[
	//			SNew(SBox)
	//			.Padding(2.f)
	//		[
	//			SNew(SCustomWidget, ECustomWidget::CWS_TextBlock_SpinBox)
	//			.Text(FText::FromString(TEXT("��������SpinBox")))
	//			.OnSpinBoxValueChanged(BIND_UOBJECT_DELEGATE(FOnFloatValueChanged, OnSpinBoxValueChangedEvent))
	//			.OnGetSpinBoxValue(BIND_UOBJECT_DELEGATE(FOnGetSpinBoxValue, OnGetSpinBoxValueEvent))
	//	]
	//	]
	//	+ SVerticalBox::Slot()
	//	.AutoHeight()
	//	[
	//		SNew(SBox)
	//		.Padding(2.f)
	//		[
	//			SNew(SCustomWidget, ECustomWidget::CWS_TextBlock_CheckBox)
	//			.Text(FText::FromString(TEXT("��������CheckBox")))
	//			.OnGetCheckBoxState(BIND_UOBJECT_DELEGATE(FOnGetCheckBoxState, OnGetCheckBoxStateEvent))
	//			.OnCheckStateChanged(BIND_UOBJECT_DELEGATE(FOnCheckStateChanged, OnCheckStateChangedEvent))
	//		]
	//	]
	//	+ SVerticalBox::Slot()
	//	.AutoHeight()
	//	[
	//		SNew(SBox)
	//		.Padding(2.f)
	//		[
	//			SNew(SCustomWidget, ECustomWidget::CWS_CheckBox_TextBlock)
	//			.Text(FText::FromString(TEXT("��������CheckBox")))
	//			.OnCheckStateChanged(BIND_UOBJECT_DELEGATE(FOnCheckStateChanged, OnCheckStateChangedEvent))
	//		]
	//	]
	//	+ SVerticalBox::Slot()
	//	.AutoHeight()
	//	[
	//		SNew(SBox)
	//		.Padding(2.f)
	//		[
	//			SNew(SCustomWidget, ECustomWidget::CWS_Button_ColorBox)
	//			.Text(FText::FromString(TEXT("ǽ����ɫ")))
	//			.OnGetLinearColor(BIND_UOBJECT_DELEGATE(FOnGetLinearColor, OnGetLinearColorEvent))
	//			.OnLinearColorValueChanged(BIND_UOBJECT_DELEGATE(FOnLinearColorValueChanged, OnLinearColorValueChangedEvent))
	//		]
	//	]
	//];

	//GEngine->GameViewport->AddViewportWidgetForPlayer(GetLocalPlayer(), VerticalBox, 1);

	// �Ż�slate��ʽ�����ʽ
	/////////////////////////////////////////////////////////////////












	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	// ��������ʾ��
	// �Ż�slate��ʽ

	//TSharedRef<SVerticalBox> Widget = SNew(SVerticalBox)
	//+ SVerticalBox::Slot()
	//.HAlign(HAlign_Center)
	//.VAlign(VAlign_Center)
	//[
	//	SNew(SButton)
	//	.OnClicked(FOnClicked::CreateUObject(this, &ATutorialsPlayerController::ShowTutorial))
	//	.Content()
	//	[
	//		SNew(STextBlock)
	//		.Text(FText::FromString(TEXT("��ʾ��������")))
	//	]
	//]
	//+ SVerticalBox::Slot()
	//.HAlign(HAlign_Center)
	//.VAlign(VAlign_Center)
	//[
	//	SNew(SButton)
	//	.OnClicked(FOnClicked::CreateUObject(this, &ATutorialsPlayerController::HideTutorial))
	//	.Content()
	//	[
	//		SNew(STextBlock)
	//		.Text(FText::FromString(TEXT("������������")))
	//	]
	//]
	//+ SVerticalBox::Slot()
	//.HAlign(HAlign_Center)
	//.VAlign(VAlign_Center)
	//[
	//	SNew(SButton)
	//	.OnClicked(FOnClicked::CreateUObject(this, &ATutorialsPlayerController::SetBorderPulsePosition))
	//	.Content()
	//	[
	//		SNew(STextBlock)
	//		.Text(FText::FromString(TEXT("����PulsePosition")))
	//	]
	//];

	//GEngine->GameViewport->AddViewportWidgetForPlayer(GetLocalPlayer(), Widget, 1);
	
	// ��������ʾ��
	// �Ż�slate��ʽ
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////








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
	TestSpinBoxValue = 10.f;
	TestCheckBoxState = ECheckBoxState::Checked;
	TestColor = FLinearColor::Green;
	///////////////////////////

	GTutorialWindow->ShowTutorial(true);
	GTutorialWindow->ShowBorderPulse(true);
	return FReply::Handled();
}

FReply ATutorialsPlayerController::HideTutorial()
{
	TestSpinBoxValue = 20.f;
	TestCheckBoxState = ECheckBoxState::Unchecked;
	TestColor = FLinearColor::Black;
	///////////////////////////

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

void ATutorialsPlayerController::OnSpinBoxValueChangedEvent(float InValue)
{
	UE_LOG(LogTemp, Warning, TEXT("ATutorialsPlayerController::HandleOnValueChanged : %f"), InValue);
	TestSpinBoxValue = InValue;
}

void ATutorialsPlayerController::OnCheckStateChangedEvent(ECheckBoxState InNewState)
{
	TestCheckBoxState = InNewState;

	if (InNewState == ECheckBoxState::Checked)
	{
		UE_LOG(LogTemp, Warning, TEXT("HandleOnCheckStateChanged::Checked"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HandleOnCheckStateChanged::Unchecked"));
	}
	
}

float ATutorialsPlayerController::OnGetSpinBoxValueEvent()
{
	return TestSpinBoxValue;
}

ECheckBoxState ATutorialsPlayerController::OnGetCheckBoxStateEvent()
{
	return TestCheckBoxState;
}

FLinearColor ATutorialsPlayerController::OnGetLinearColorEvent()
{
	return TestColor;
}

void ATutorialsPlayerController::OnLinearColorValueChangedEvent(FLinearColor InLinearColor)
{
	TestColor = InLinearColor;
}

void ATutorialsPlayerController::OnComboBoxSelectionChanged(const FString& SelectItemName)
{
	UE_LOG(LogTemp, Warning, TEXT("SelectItemName : %s"), *SelectItemName);
}

//TSharedRef<SWidget> ATutorialsPlayerController::MakeDetailWidget()
//{
//	FDetailBuilder DetailBuilder;
//	DetailBuilder.AddEntryBlock(
//		EWidgetType::WT_TEXTBLOCK_CHECK,
//		FText::FromString(TEXT("")),
//		FOnCheckStateChanged::CreateUObject(this, &ATutorialsPlayerController::OnCheckStateChangedEvent)
//	);
//
//	return SNew(SWindow);
//}

void ATutorialsPlayerController::OnButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("OnButtonClicked()"));
}
