// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

DECLARE_DELEGATE_RetVal( float, FOnGetSpinBoxValue)
DECLARE_DELEGATE_RetVal(ECheckBoxState, FOnGetCheckBoxState)
DECLARE_DELEGATE_RetVal(FLinearColor, FOnGetLinearColor)

UENUM()
namespace ECustomWidget
{
	enum Style
	{
		None,
		CWS_TextBlock_SpinBox,
		CWS_TextBlock_CheckBox,
		CWS_CheckBox_TextBlock,
		CWS_Button_ColorBox
	};
}

/**
* A numerical entry box that allows for direct entry of the number or allows the user to click and slide the number.
*/
class SCustomWidget : public SCompoundWidget
{
public:


	SLATE_BEGIN_ARGS(SCustomWidget)
	{}

	SLATE_ARGUMENT(FText, Text)
	//SLATE_ARGUMENT(FLinearColor, ColorCategory)

	/** Called when the value is changed by slider or typing */
	SLATE_EVENT( FOnFloatValueChanged, OnSpinBoxValueChanged )
	SLATE_EVENT( FOnCheckStateChanged, OnCheckStateChanged )
	SLATE_EVENT( FOnGetSpinBoxValue, OnGetSpinBoxValue )
	SLATE_EVENT( FOnGetCheckBoxState, OnGetCheckBoxState )
	SLATE_EVENT( FOnGetLinearColor, OnGetLinearColor )
	SLATE_EVENT( FOnLinearColorValueChanged, OnLinearColorValueChanged )
	
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, ECustomWidget::Style _Style);

protected:
	void OnSpinBoxValueChangedEvent(float InValue);

	void OnCheckStateChangedEvent(ECheckBoxState InNewState);

	FReply OnSelectColorClickedEvent();

	void OnSelectColorChangedEvent(FLinearColor NewColor);

	float OnGetSpinBoxValueEvent() const;

	ECheckBoxState OnGetCheckBoxStateEvent() const;

	FLinearColor  OnGetLinearColorEvent() const;

private:

	ECustomWidget::Style Style;

	FLinearColor ColorCategory;

	FOnFloatValueChanged OnSpinBoxValueChanged;

	/** Delegate called when the check box changes state */
	FOnCheckStateChanged OnCheckStateChanged;

	/** Delegate to get the value if supplied from an external source */
	FOnGetSpinBoxValue OnGetSpinBoxValue;

	FOnGetCheckBoxState OnGetCheckBoxState;

	FOnGetLinearColor OnGetLinearColor;

	FOnLinearColorValueChanged OnLinearColorValueChanged;

};