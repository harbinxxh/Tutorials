
#include "Tutorials.h"
#include "Runtime/Analytics/Analytics/Public/Interfaces/IAnalyticsProvider.h"
#include "VRSEditorStyleSet.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "SDetailWidget.h"
#include "Runtime/AppFramework/Public/Widgets/Colors/SColorPicker.h"
// tmp test
#include "TutorialsPlayerController.h"


void SDetailWidget::Construct(const FArguments& InArgs, TArray< TSharedRef < const FDetailEntryBlock > >& InDetailBuilderList)
{
	DetailBuilderList = InDetailBuilderList;

	TSharedPtr<SVerticalBox> VerticalBox = nullptr;
	ChildSlot
	.Padding(0.0f, 2.0f, 0.0f, 0.0f)
	[
		SNew(SBox)
		.MinDesiredWidth(300)
		.MinDesiredHeight(600)
		[
			SNew(SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("BlackBrush"))
			.Padding(FMargin(0.0f, 3.0f, 16, 3.0f))
			.BorderBackgroundColor(FLinearColor(.6, .6, .6, 1.0f))
			[
				SAssignNew(VerticalBox, SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(0,0,0,2)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					[
						SNew(STextBlock)
						.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12))
						.Text(FText::FromString(TEXT("ø’º‰ Ù–‘")))
					]
				]
			]
		]
	];

	// Loop TArray
	for (TArray< TSharedRef < const FDetailEntryBlock > >::TIterator It = InDetailBuilderList.CreateIterator(); It; ++It)
	{
		TSharedRef < const FDetailEntryBlock >& EntryBlock = *It;

		TSharedRef<SWidget> Widget = OnEntryBlockAnalyse(EntryBlock);

		VerticalBox->AddSlot()
		.AutoHeight()
		.Padding(20,0,20,2)
		[
			Widget
		];
	}
}


TSharedPtr< SWidget >& SDetailWidget::GetEntryBlockSWidget(const FString InEntryBlockID)
{
	TSharedPtr<SWidget>* TmpSWidget = SWidgetListMap.Find(InEntryBlockID);
	return *TmpSWidget;
}


TSharedRef<SWidget> SDetailWidget::OnEntryBlockAnalyse(TSharedRef < const FDetailEntryBlock >& EntryBlock)
{
	TSharedRef<SWidget> Widget = SNullWidget::NullWidget;

	if (EntryBlock->BlockID.IsEmpty())
	{
		return Widget;
	}

	if (EntryBlock->Type == EWidgetType::WT_BUTTON)
	{
		Widget = OnEntryBlockButton(EntryBlock);
	}
	else if (EntryBlock->Type == EWidgetType::WT_TEXTBLOCK_CHECK)
	{
		Widget = OnEntryBlockTextBlockCheck(EntryBlock);
	}
	else if (EntryBlock->Type == EWidgetType::WT_TEXTBLOCK_COMBO)
	{
		Widget = OnEntryBlockTextBlockCombo(EntryBlock);
	}
	else if (EntryBlock->Type == EWidgetType::WT_TEXTBLOCK_SPINBOX)
	{
		Widget = OnEntryBlockTextBlockSpinBox(EntryBlock);
	}
	else if (EntryBlock->Type == EWidgetType::WT_TEXTBLOCK_EDITABLETEXTBOX)
	{
		Widget = OnEntryBlockTextBlockEditableTextBox(EntryBlock);
	}

	return Widget;
}


TSharedRef<SWidget> SDetailWidget::OnEntryBlockButton(TSharedRef < const FDetailEntryBlock >& EntryBlock)
{
	OnButtonClicked = EntryBlock->OnButtonClicked;

	TSharedRef<SWidget> Widget = SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Center)
	[
		SNew(SButton)
		.OnClicked(this, &SDetailWidget::OnButtonClickedEvent, EntryBlock->BlockID)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Content()
		[
			SNew(SBox)
			.HeightOverride(20)
			[
				SNew(STextBlock)
				.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12))
				.Text(EntryBlock->Text)
				]
			]
	];

	SWidgetListMap.Add(EntryBlock->BlockID, Widget);
	return Widget;
}


TSharedRef<SWidget> SDetailWidget::OnEntryBlockTextBlockCheck(TSharedRef < const FDetailEntryBlock >& EntryBlock)
{
	OnCheckStateChanged = EntryBlock->OnCheckStateChanged;

	TSharedRef<SWidget> Widget = SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Center)
	.Padding(5.f)
	.AutoWidth()
	[
		SNew(STextBlock)
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14))
		.ColorAndOpacity(FLinearColor(1, 1, 1, 0.5))
		.Text(EntryBlock->Text)
	]
	+ SHorizontalBox::Slot()
	.Padding(FMargin(5.0f, 0.0f, 0.0f, 0.0f))
	.AutoWidth()
	[
		SNew(SCheckBox)
		.OnCheckStateChanged(this, &SDetailWidget::OnCheckStateChangedEvent, EntryBlock->BlockID)
	];

	SWidgetListMap.Add(EntryBlock->BlockID, Widget);
	return Widget;
}


TSharedRef<SWidget> SDetailWidget::OnEntryBlockTextBlockCombo(TSharedRef < const FDetailEntryBlock >& EntryBlock)
{
	OnComboBoxSelectionChanged = EntryBlock->OnComboBoxSelectionChanged;
	RoomComboList = EntryBlock->RoomComboList;
	SelectorComboBoxSelectedItem = RoomComboList[0];
	TSharedRef<SWidget> Widget = SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Center)
	.Padding(5.f)
	.AutoWidth()
	[
		SNew(STextBlock)
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14))
		.ColorAndOpacity(FLinearColor(1, 1, 1, 0.5))
		.Text(EntryBlock->Text)
	]
	+ SHorizontalBox::Slot()
	.Padding(FMargin(5.0f, 0.0f, 0.0f, 0.0f))
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Center)
	.FillWidth(1)
	[
		SNew(SComboBox< TSharedPtr<FString> >)
		.OptionsSource(&RoomComboList)
		.OnSelectionChanged(this, &SDetailWidget::HandleSelectorComboBoxSelectionChanged, EntryBlock->BlockID)
		.OnGenerateWidget(this, &SDetailWidget::HandleComboBoxGenerateWidget, EntryBlock->BlockID)
		.Content()
		[
			SNew(STextBlock)
			.Text(this, &SDetailWidget::HandleSelectorComboBoxText)
		]
	];

	SWidgetListMap.Add(EntryBlock->BlockID, Widget);
	return Widget;
}

TSharedRef<SWidget> SDetailWidget::OnEntryBlockTextBlockSpinBox(TSharedRef < const FDetailEntryBlock >& EntryBlock)
{
	OnSpinBoxValueChanged = EntryBlock->OnSpinBoxValueChanged;

	TSharedRef<SWidget> Widget = SNew(SHorizontalBox)
	+ SHorizontalBox::Slot()
	.HAlign(HAlign_Left)
	.VAlign(VAlign_Center)
	.Padding(5.f)
	.AutoWidth()
	[
		SNew(STextBlock)
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14))
		.ColorAndOpacity(FLinearColor(1, 1, 1, 0.5))
		.Text(EntryBlock->Text)
	]
	+ SHorizontalBox::Slot()
	.Padding(FMargin(5.0f, 0.0f, 0.0f, 0.0f))
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Center)
	.AutoWidth()
	[
		SNew(SSpinBox<float>)
		.MinValue(0.f)
		.MaxValue(100.f)
		.Delta(1.f)
		.MinDesiredWidth(122.f)
		.Value(EntryBlock->SpinBoxValue)
		.OnValueChanged(this, &SDetailWidget::OnSpinBoxValueChangedEvent, EntryBlock->BlockID)
	];

	SWidgetListMap.Add(EntryBlock->BlockID, Widget);
	return Widget;
}

TSharedRef<SWidget> SDetailWidget::OnEntryBlockTextBlockEditableTextBox(TSharedRef < const FDetailEntryBlock >& EntryBlock)
{
	OnEditableTextBoxChanged = EntryBlock->OnEditableTextChanged;

	TSharedRef<SWidget> Widget = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Padding(5.f)
		.AutoWidth()
		[
			SNew(STextBlock)
			.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14))
			.ColorAndOpacity(FLinearColor(1, 1, 1, 0.5))
			.Text(EntryBlock->Text)
		]
		+ SHorizontalBox::Slot()
		.Padding(FMargin(5.0f, 0.0f, 0.0f, 0.0f))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.AutoWidth()
		[
			SNew(SEditableTextBox)
			.Text(EntryBlock->EditableText)
			.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 12))
			.OnTextCommitted(this, &SDetailWidget::OnEditableTextBoxChangedEvent, EntryBlock->BlockID)
			.OnTextChanged(this, &SDetailWidget::OnEditableTextBoxChangedEvent, ETextCommit::Default, EntryBlock->BlockID)
		];

		SWidgetListMap.Add(EntryBlock->BlockID, Widget);
		return Widget;
}

FReply SDetailWidget::OnButtonClickedEvent(FString BlockID)
{
	TSharedRef<const FDetailEntryBlock >& EntryBlock = OnFindEntryBlock(BlockID);
	if (!EntryBlock->BlockID.IsEmpty())
	{
		EntryBlock->OnButtonClicked.ExecuteIfBound();
	}
	//OnButtonClicked.ExecuteIfBound();
	return FReply::Handled();
}


void SDetailWidget::OnCheckStateChangedEvent(ECheckBoxState InNewState, FString BlockID)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCheckStateChangedEvent : %s"), *BlockID);

	TSharedRef<const FDetailEntryBlock >& EntryBlock = OnFindEntryBlock(BlockID);
	if (!EntryBlock->BlockID.IsEmpty())
	{
		EntryBlock->OnCheckStateChanged.ExecuteIfBound(InNewState);
	}
	//OnCheckStateChanged.ExecuteIfBound(InNewState);
}

TSharedRef<SWidget> SDetailWidget::HandleComboBoxGenerateWidget(TSharedPtr<FString> InItem, FString BlockID)
{
	return SNew(STextBlock).Text( FText::FromString(*InItem) );
}

void SDetailWidget::HandleSelectorComboBoxSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FString BlockID)
{
	FString Selection = *NewSelection;

	TSharedRef<const FDetailEntryBlock >& EntryBlock = OnFindEntryBlock(BlockID);
	if (!EntryBlock->BlockID.IsEmpty())
	{
		EntryBlock->OnComboBoxSelectionChanged.ExecuteIfBound(Selection);
	}
	//OnComboBoxSelectionChanged.ExecuteIfBound(Selection);
	SelectorComboBoxSelectedItem = NewSelection;
}

FText SDetailWidget::HandleSelectorComboBoxText() const
{
	return SelectorComboBoxSelectedItem.IsValid() ? FText::FromString(*SelectorComboBoxSelectedItem) : FText::GetEmpty();
}

void SDetailWidget::OnSpinBoxValueChangedEvent(float InValue, FString BlockID)
{
	TSharedRef<const FDetailEntryBlock >& EntryBlock = OnFindEntryBlock(BlockID);
	if (!EntryBlock->BlockID.IsEmpty())
	{
		EntryBlock->OnSpinBoxValueChanged.ExecuteIfBound(InValue);
	}
	//OnSpinBoxValueChanged.ExecuteIfBound(InValue);
}

void SDetailWidget::OnEditableTextBoxChangedEvent(const FText& InText, ETextCommit::Type InCommitType, FString BlockID)
{
	TSharedRef<const FDetailEntryBlock >& EntryBlock = OnFindEntryBlock(BlockID);
	if (!EntryBlock->BlockID.IsEmpty())
	{
		EntryBlock->OnEditableTextChanged.ExecuteIfBound(InText);
	}
	//OnEditableTextBoxChanged.ExecuteIfBound(InText);
}


TSharedRef<const FDetailEntryBlock >& SDetailWidget::OnFindEntryBlock(FString& InBlockID)
{
	// Loop TArray
	for (TArray< TSharedRef < const FDetailEntryBlock > >::TIterator It = DetailBuilderList.CreateIterator(); It; ++It)
	{
		TSharedRef < const FDetailEntryBlock >& EntryBlock = *It;

		if (EntryBlock->BlockID == InBlockID)
		{
			return EntryBlock;
		}
	}
	static TSharedRef<const FDetailEntryBlock > EntryBlockTemp(new FDetailEntryBlock());
	return EntryBlockTemp;
}

