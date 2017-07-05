
#include "Tutorials.h"
#include "Runtime/Analytics/Analytics/Public/Interfaces/IAnalyticsProvider.h"
#include "VRSEditorStyleSet.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "SCustomWidget.h"


void SCustomWidget::Construct(const FArguments& InArgs, ECustomWidget::Style _Style)
{
	Style = _Style;

	OnClicked = InArgs._OnClicked;

	TSharedPtr<SHorizontalBox> HorizontalBox = nullptr;

	ChildSlot
	[
		SAssignNew(HorizontalBox, SHorizontalBox)
	];

	TSharedRef<SWidget> TextSwidget = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.Padding(5.0f)
		.AutoWidth()
		[
			SNew(STextBlock)
			.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 14))
			.ColorAndOpacity(FLinearColor(1, 1, 1, 0.5))
			.Text(InArgs._Text)
		]
		+ SHorizontalBox::Slot()
		.Padding(FMargin(5.0f, 0.0f, 0.0f, 0.0f))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		.FillWidth(1)
		[
			SNew(SSpinBox<float>)
			.MinValue(0.f)
			.MaxValue(100.f)
			.Delta(1.f)
			.MinDesiredWidth(100)
		];

	if (_Style == ECustomWidget::CWS_TextBlock)
	{
		HorizontalBox->AddSlot()
		[
			TextSwidget
		];
	}

}
