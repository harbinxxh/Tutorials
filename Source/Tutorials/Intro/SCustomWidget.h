// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once


UENUM()
namespace ECustomWidget
{
	enum Style
	{
		None,
		CWS_TextBlock,
		CWS_CheckBox_Left,
		CWS_CheckBox_Right
	};
}



/**
* The widget which displays 'floating' content
*/
class SCustomWidget : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SCustomWidget)
		: _Text()
	{}

	SLATE_ARGUMENT(FText, Text)

	/** Delegate fired when the button is clicked */
	SLATE_EVENT(FSimpleDelegate, OnClicked)
	
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, ECustomWidget::Style _Style);

private:

	ECustomWidget::Style Style;

	/** Box that contains varied content for current custom widget */
	TSharedPtr<SHorizontalBox> ContentBox;


	/** Delegate fired when the back button is clicked */
	FSimpleDelegate OnClicked;

};