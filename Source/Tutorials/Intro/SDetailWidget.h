// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once


DECLARE_DELEGATE_OneParam(FOnComboBoxSelectionChanged, const FString& /*SelectItemName*/);
DECLARE_DELEGATE_OneParam(FOnEditableTextBoxChanged, const FText&);

class FDetailEntryBlock;
class FDetailBuilder;


UENUM()
namespace EWidgetType
{
	enum Type
	{
		WT_NONE,
		WT_BUTTON,
		WT_TEXTBLOCK_BUTTON,
		WT_TEXTBLOCK_CHECK,
		WT_TEXTBLOCK_COMBO,
		WT_TEXTBLOCK_SPINBOX,
		WT_TEXTBLOCK_EDITABLETEXTBOX
	};
}

typedef TMap<FString, TSharedPtr<SWidget> > SWidgetMap;

class SDetailWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDetailWidget)
	{}
	
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TArray< TSharedRef < const FDetailEntryBlock > >& InDetailBuilderList);

	TSharedPtr< SWidget >& GetEntryBlockSWidget(const FString InEntryBlockID);

protected:
	
	TSharedRef<SWidget> OnEntryBlockAnalyse(TSharedRef < const FDetailEntryBlock >& EntryBlock);
	TSharedRef<SWidget> OnEntryBlockButton(TSharedRef < const FDetailEntryBlock >& EntryBlock);
	TSharedRef<SWidget> OnEntryBlockTextBlockCheck(TSharedRef < const FDetailEntryBlock >& EntryBlock);
	TSharedRef<SWidget> OnEntryBlockTextBlockCombo(TSharedRef < const FDetailEntryBlock >& EntryBlock);
	TSharedRef<SWidget> OnEntryBlockTextBlockSpinBox(TSharedRef < const FDetailEntryBlock >& EntryBlock);
	TSharedRef<SWidget> OnEntryBlockTextBlockEditableTextBox(TSharedRef < const FDetailEntryBlock >& EntryBlock);

	FReply OnButtonClickedEvent(FString BlockID);
	void OnCheckStateChangedEvent(ECheckBoxState InNewState, FString BlockID);

	/** Label utility. */
	TSharedRef<SWidget> HandleComboBoxGenerateWidget(TSharedPtr<FString> InItem, FString BlockID);

	// Callback for changing the selector combo box's selection in SComboBox example.
	void HandleSelectorComboBoxSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo, FString BlockID);

	// Callback for getting the text of the selector combo box in the SComboBox example.
	FText HandleSelectorComboBoxText() const;

	// Callback for getting the spin value
	void OnSpinBoxValueChangedEvent(float InValue, FString BlockID);

	/** Delegate to commit workspace text to settings */
	void OnEditableTextBoxChangedEvent(const FText& InText, ETextCommit::Type InCommitType, FString BlockID);

	TSharedRef<const FDetailEntryBlock >& OnFindEntryBlock(FString& InBlockID);

private:
	FSimpleDelegate OnButtonClicked;

	/** Delegate called when the check box changes state */
	FOnCheckStateChanged OnCheckStateChanged;

	FOnComboBoxSelectionChanged OnComboBoxSelectionChanged;

	// Holds the selector combo box in the SComboBox demo.
	TArray< TSharedPtr< FString > > RoomComboList;
	
	// Holds the selected text in the SComboBox example.
	TSharedPtr<FString>	SelectorComboBoxSelectedItem;

	// Delegate SpinBox Value Change
	FOnFloatValueChanged OnSpinBoxValueChanged;

	// Delegate EditableTextBox Text Changed
	FOnEditableTextBoxChanged OnEditableTextBoxChanged;

	SWidgetMap SWidgetListMap;

	TArray< TSharedRef < const FDetailEntryBlock > > DetailBuilderList;
};


class FDetailEntryBlock
{
public:
	FDetailEntryBlock()
		: BlockID(TEXT("")),
		Type(EWidgetType::WT_NONE),
		Text(FText::FromString(TEXT("")))
	{}

	// EntryBlockID
	FString BlockID;

	// 控件类型
	EWidgetType::Type Type;

	// 文本描述
	FText Text;

	// Combo Item List
	TArray< TSharedPtr< FString > > RoomComboList;

	// Initial SpinBox Value
	float SpinBoxValue;

	// Initial EditableTextBox Text
	FText EditableText;

	/** Delegate Callback*/
	// Delegate CheckBox
	FOnCheckStateChanged OnCheckStateChanged;

	// Delegate Button
	FSimpleDelegate OnButtonClicked;

	// Delegate ComboBox
	FOnComboBoxSelectionChanged OnComboBoxSelectionChanged;

	// Delegate SpinBox Value Change
	FOnFloatValueChanged OnSpinBoxValueChanged;

	// Delegate EditableTextBox Text Changed
	FOnEditableTextBoxChanged OnEditableTextChanged;
};


class FDetailBuilder
{
public:
	// Button
	void AddButtonBlock(const FString& InBlockID, EWidgetType::Type InType, const FText& InText, const FSimpleDelegate& InOnButtonClicked = FSimpleDelegate())
	{
		TSharedRef< FDetailEntryBlock > EntryBlock(new FDetailEntryBlock());
		EntryBlock->BlockID = InBlockID;
		EntryBlock->Type = InType;
		EntryBlock->Text = InText;
		EntryBlock->OnButtonClicked = InOnButtonClicked;
		DetailBuilderList.Add(EntryBlock);
	}

	// Check
	void AddCheckBoxBlock(const FString& InBlockID, EWidgetType::Type InType, const FText& InText, const FOnCheckStateChanged& InOnCheckStateChanged = FOnCheckStateChanged())
	{
		TSharedRef< FDetailEntryBlock > EntryBlock(new FDetailEntryBlock());
		EntryBlock->BlockID = InBlockID;
		EntryBlock->Type = InType;
		EntryBlock->Text = InText;
		EntryBlock->OnCheckStateChanged = InOnCheckStateChanged;
		DetailBuilderList.Add(EntryBlock);
	}

	// Combo
	void AddComboBoxBlock(const FString& InBlockID, EWidgetType::Type InType, const FText& InText, const TArray< TSharedPtr< FString > >& InRoomComboList, const FOnComboBoxSelectionChanged& InOnComboBoxSelectionChanged = FOnComboBoxSelectionChanged())
	{
		TSharedRef< FDetailEntryBlock > EntryBlock(new FDetailEntryBlock());
		EntryBlock->BlockID = InBlockID;
		EntryBlock->Type = InType;
		EntryBlock->Text = InText;
		EntryBlock->RoomComboList = InRoomComboList;
		EntryBlock->OnComboBoxSelectionChanged = InOnComboBoxSelectionChanged;
		DetailBuilderList.Add(EntryBlock);
	}

	// SpinBox
	void AddSpinBoxBlock(const FString& InBlockID, EWidgetType::Type InType, const FText& InText, const float InSpinBoxValue, const FOnFloatValueChanged& InOnSpinBoxValueChanged = FOnFloatValueChanged())
	{
		TSharedRef< FDetailEntryBlock > EntryBlock(new FDetailEntryBlock());
		EntryBlock->BlockID = InBlockID;
		EntryBlock->Type = InType;
		EntryBlock->Text = InText;
		EntryBlock->SpinBoxValue = InSpinBoxValue;
		EntryBlock->OnSpinBoxValueChanged = InOnSpinBoxValueChanged;

		DetailBuilderList.Add(EntryBlock);
	}

	// SEditableTextBox
	void AddEditableTextBoxBlock(const FString& InBlockID, EWidgetType::Type InType, const FText& InText, const FText& InEditableText, const FOnEditableTextBoxChanged& InOnEditableTextBoxChanged = FOnEditableTextBoxChanged())
	{
		TSharedRef< FDetailEntryBlock > EntryBlock(new FDetailEntryBlock());
		EntryBlock->BlockID = InBlockID;
		EntryBlock->Type = InType;
		EntryBlock->Text = InText;
		EntryBlock->EditableText = InEditableText;
		EntryBlock->OnEditableTextChanged = InOnEditableTextBoxChanged;

		DetailBuilderList.Add(EntryBlock);
	}

	TSharedRef< class SDetailWidget > MakeWidget()
	{
		return SNew(SDetailWidget, DetailBuilderList);
	}

	TArray< TSharedRef < const FDetailEntryBlock > > DetailBuilderList;
};