// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

DECLARE_DELEGATE_OneParam(FOnComboBoxSelectionChanged, const FString& /*SelectItemName*/);

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
		WT_TEXTBLOCK_COMBO
	};
}

typedef TMap<FString, TSharedPtr<SWidget> > SWidgetMap;

class SDetailWidget : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SDetailWidget)
	{}
	
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, TArray< TSharedRef < const FDetailEntryBlock > >& DetailBuilderList);

	TSharedPtr< SWidget >& GetEntryBlockSWidget(const FString InEntryBlockID);

protected:
	
	TSharedRef<SWidget> OnEntryBlockAnalyse(TSharedRef < const FDetailEntryBlock >& EntryBlock);
	TSharedRef<SWidget> OnEntryBlockButton(TSharedRef < const FDetailEntryBlock >& EntryBlock);
	TSharedRef<SWidget> OnEntryBlockTextBlockCheck(TSharedRef < const FDetailEntryBlock >& EntryBlock);
	TSharedRef<SWidget> OnEntryBlockTextBlockCombo(TSharedRef < const FDetailEntryBlock >& EntryBlock);

	FReply OnButtonClickedEvent();
	void OnCheckStateChangedEvent(ECheckBoxState InNewState);

	/** Label utility. */
	TSharedRef<SWidget> HandleComboBoxGenerateWidget(TSharedPtr<FString> InItem);

	// Callback for changing the selector combo box's selection in SComboBox example.
	void HandleSelectorComboBoxSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);

	// Callback for getting the text of the selector combo box in the SComboBox example.
	FText HandleSelectorComboBoxText() const;

private:
	FSimpleDelegate OnButtonClicked;

	/** Delegate called when the check box changes state */
	FOnCheckStateChanged OnCheckStateChanged;

	FOnComboBoxSelectionChanged OnComboBoxSelectionChanged;

	// Holds the selector combo box in the SComboBox demo.
	TArray< TSharedPtr< FString > > RoomComboList;
	
	// Holds the selected text in the SComboBox example.
	TSharedPtr<FString>	SelectorComboBoxSelectedItem;

	SWidgetMap SWidgetListMap;
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

	/** Delegate Callback*/
	FOnCheckStateChanged OnCheckStateChanged;
	FSimpleDelegate OnButtonClicked;
	FOnComboBoxSelectionChanged OnComboBoxSelectionChanged;
};


class FDetailBuilder
{
public:
	// Button
	void AddEntryBlock(const FString& InBlockID, EWidgetType::Type InType, const FText& InText, const FSimpleDelegate& InOnButtonClicked)
	{
		TSharedRef< FDetailEntryBlock > EntryBlock(new FDetailEntryBlock());
		EntryBlock->BlockID = InBlockID;
		EntryBlock->Type = InType;
		EntryBlock->Text = InText;
		EntryBlock->OnButtonClicked = InOnButtonClicked;
		DetailBuilderList.Add(EntryBlock);
	}

	// Check
	void AddEntryBlock(const FString& InBlockID, EWidgetType::Type InType, const FText& InText, const FOnCheckStateChanged& InOnCheckStateChanged)
	{
		TSharedRef< FDetailEntryBlock > EntryBlock(new FDetailEntryBlock());
		EntryBlock->BlockID = InBlockID;
		EntryBlock->Type = InType;
		EntryBlock->Text = InText;
		EntryBlock->OnCheckStateChanged = InOnCheckStateChanged;
		DetailBuilderList.Add(EntryBlock);
	}

	// Combo
	void AddEntryBlock(const FString& InBlockID, EWidgetType::Type InType, const FText& InText, const TArray< TSharedPtr< FString > >& InRoomComboList, const FOnComboBoxSelectionChanged& InOnComboBoxSelectionChanged)
	{
		TSharedRef< FDetailEntryBlock > EntryBlock(new FDetailEntryBlock());
		EntryBlock->BlockID = InBlockID;
		EntryBlock->Type = InType;
		EntryBlock->Text = InText;
		EntryBlock->RoomComboList = InRoomComboList;
		EntryBlock->OnComboBoxSelectionChanged = InOnComboBoxSelectionChanged;
		DetailBuilderList.Add(EntryBlock);
	}


	TSharedRef< class SDetailWidget > MakeWidget()
	{
		return SNew(SDetailWidget, DetailBuilderList);
	}

	//TSharedRef< class SWidget > MakeWidget()
	//{
	//	TSharedRef<SWidget> DetailWidget = SNew(SDetailWidget, DetailBuilderList);
	//	return DetailWidget;
	//}


	TArray< TSharedRef < const FDetailEntryBlock > > DetailBuilderList;
};