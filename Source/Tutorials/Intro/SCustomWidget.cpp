
#include "Tutorials.h"
#include "Runtime/Analytics/Analytics/Public/Interfaces/IAnalyticsProvider.h"
#include "VRSEditorStyleSet.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "SCustomWidget.h"
#include "Runtime/AppFramework/Public/Widgets/Colors/SColorPicker.h"

// tmp test
#include "TutorialsPlayerController.h"


void SCustomWidget::Construct(const FArguments& InArgs, ECustomWidget::Style _Style)
{
	Style = _Style;

	OnSpinBoxValueChanged = InArgs._OnSpinBoxValueChanged;
	OnCheckStateChanged = InArgs._OnCheckStateChanged;
	OnGetSpinBoxValue = InArgs._OnGetSpinBoxValue;
	OnGetCheckBoxState = InArgs._OnGetCheckBoxState;
	OnGetLinearColor = InArgs._OnGetLinearColor;
	OnLinearColorValueChanged = InArgs._OnLinearColorValueChanged;

	TSharedPtr<SHorizontalBox> HorizontalBox = nullptr;

	ChildSlot
	[
		SAssignNew(HorizontalBox, SHorizontalBox)
	];

	// ÃèÊöÎÄ×Ö
	TSharedRef<SWidget> TextBlock = SNew(STextBlock)
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14))
		.ColorAndOpacity(FLinearColor(1, 1, 1, 0.5))
		.Text(InArgs._Text);

	// SSpinBox
	TSharedRef<SWidget> SpinBox = SNew(SSpinBox<float>)
		.MinValue(0.f)
		.MaxValue(100.f)
		.Delta(1.f)
		.MinDesiredWidth(100)
		.Value( this, &SCustomWidget::OnGetSpinBoxValueEvent)
		.OnValueChanged(this, &SCustomWidget::OnSpinBoxValueChangedEvent);

	// CheckBox
	TSharedRef<SWidget> CheckBox = SNew(SCheckBox)
		.IsChecked(this, &SCustomWidget::OnGetCheckBoxStateEvent)
		.OnCheckStateChanged(this, &SCustomWidget::OnCheckStateChangedEvent);

	// Button
	TSharedRef<SWidget> Button = SNew(SButton)
	.OnClicked(this, &SCustomWidget::OnSelectColorClickedEvent)
	.Content()
	[
		SNew(SBorder)
		//.BorderBackgroundColor(FSlateColor::FSlateColor(OnGetLinearColor))
		.Content()
		[
			SNew(SBox)
			.WidthOverride(24)
			.HeightOverride(24)
			//.Content()
			//[
			//	SNew(STextBlock)
			//	.Text(FText::FromString(TEXT("Color Button")))
			//]
		]
	];

	if (_Style == ECustomWidget::CWS_TextBlock_SpinBox)
	{
		TSharedRef<SWidget> TextSpinBoxSwidget = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.Padding(5.0f)
		.AutoWidth()
		[
			TextBlock
		]
		+ SHorizontalBox::Slot()
		.Padding(FMargin(5.0f, 0.0f, 0.0f, 0.0f))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		.FillWidth(1)
		[
			SpinBox
		];

		HorizontalBox->AddSlot()
		[
			TextSpinBoxSwidget
		];
	}
	else if (_Style == ECustomWidget::CWS_TextBlock_CheckBox)
	{
		TSharedRef<SWidget> TextCheckBoxSwidget = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.Padding(5.0f)
		.AutoWidth()
		[
			TextBlock
		]
		+ SHorizontalBox::Slot()
		.Padding(FMargin(5.0f, 0.0f, 0.0f, 0.0f))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		.FillWidth(1)
		[
			CheckBox
		];

		HorizontalBox->AddSlot()
		[
			TextCheckBoxSwidget
		];
	}
	else if (_Style == ECustomWidget::CWS_CheckBox_TextBlock)
	{
		TSharedRef<SWidget> CheckBoxTextBlockSwidget = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.Padding(5.0f)
		.AutoWidth()
		[
			CheckBox
		]
		+ SHorizontalBox::Slot()
		.Padding(FMargin(5.0f, 0.0f, 0.0f, 0.0f))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		.FillWidth(1)
		[
			TextBlock
		];

		HorizontalBox->AddSlot()
		[
			CheckBoxTextBlockSwidget
		];
	}
	else if (_Style == ECustomWidget::CWS_Button_ColorBox)
	{
		TSharedRef<SWidget> TextBlockColorBoxSwidget = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.Padding(5.0f)
		.AutoWidth()
		[
			TextBlock
		]
		+ SHorizontalBox::Slot()
		.Padding(FMargin(5.0f, 0.0f, 0.0f, 0.0f))
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.FillWidth(1)
		[
			Button
		];

		HorizontalBox->AddSlot()
		[
			TextBlockColorBoxSwidget
		];
	}
}

void SCustomWidget::OnSpinBoxValueChangedEvent(float InValue)
{
	OnSpinBoxValueChanged.ExecuteIfBound(InValue);
}

void SCustomWidget::OnCheckStateChangedEvent(ECheckBoxState InNewState)
{
	OnCheckStateChanged.ExecuteIfBound(InNewState);
}

FReply SCustomWidget::OnSelectColorClickedEvent()
{
	FColorPickerArgs PickerArgs;
	//PickerArgs.InitialColorOverride = Border_WallColor->Background.TintColor.GetSpecifiedColor();
	FLinearColor LinearColro = OnGetLinearColorEvent();
	PickerArgs.InitialColorOverride = LinearColro;
	PickerArgs.bUseAlpha = false;
	PickerArgs.DisplayGamma = TAttribute<float>::Create(TAttribute<float>::FGetter::CreateUObject(GEngine, &UEngine::GetDisplayGamma));
	PickerArgs.OnColorCommitted = FOnLinearColorValueChanged::CreateSP(this, &SCustomWidget::OnSelectColorChangedEvent);
	OpenColorPicker(PickerArgs);

	return FReply::Handled();
}

void SCustomWidget::OnSelectColorChangedEvent(FLinearColor NewColor)
{
	OnLinearColorValueChanged.ExecuteIfBound(NewColor);
}

float SCustomWidget::OnGetSpinBoxValueEvent() const
{
	float Value = 0.f;
	if (OnGetSpinBoxValue.IsBound())
	{
		Value = OnGetSpinBoxValue.Execute();
	}
	return Value;
}

ECheckBoxState SCustomWidget::OnGetCheckBoxStateEvent() const
{
	ECheckBoxState CheckBoxState = ECheckBoxState::Unchecked;
	if ( OnGetCheckBoxState.IsBound() )
	{
		CheckBoxState = OnGetCheckBoxState.Execute();
	}
	return CheckBoxState;
}

FLinearColor SCustomWidget::OnGetLinearColorEvent() const
{
	FLinearColor LinearColor = FLinearColor::White;
	if ( OnGetLinearColor.IsBound())
	{
		LinearColor = OnGetLinearColor.Execute();
	}
	return LinearColor;
}
