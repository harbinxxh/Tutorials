
#include "Tutorials.h"
#include "SVRSTutorialContent.h"
#include "Runtime/Analytics/Analytics/Public/Interfaces/IAnalyticsProvider.h"
#include "VRSEditorStyleSet.h"
#include "TutorialsPlayerController.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "VRSTutorialContentMgr.h"
#include "VRSWidgetTutorialContentPanel.h"

#define LOCTEXT_NAMESPACE "SVRSTutorialContent"

namespace TutorialConstants
{
	const float BorderPulseAnimationLength = 0.75f;
	const float BorderIntroAnimationLength = 0.4f;
	const float ContentIntroAnimationLength = 0.25f;
	const float MinBorderOpacity = 0.1f;
	const float ShadowScale = 8.0f;
	const float MaxBorderOffset = 8.0f;
	const FMargin BorderSizeStandalone(24.0f, 24.0f);
	const FMargin BorderSize(24.0f, 24.0f, 24.0f, 62.0f);
}

const float ContentOffset = 10.0f;

void SVRSTutorialContent::Construct(const FArguments& InArgs, FGeometry& InGeometry)
{
	CachedGeometry = InGeometry;

	BorderIntroAnimation.AddCurve(0.0f, TutorialConstants::BorderIntroAnimationLength, ECurveEaseFunction::CubicOut);
	BorderPulseAnimation.AddCurve(0.0f, TutorialConstants::BorderPulseAnimationLength, ECurveEaseFunction::Linear);
	BorderIntroAnimation.Play(this->AsShared());

	// Set the border pulse to play on a loop and immediately pause it - will be resumed when needed
	BorderPulseAnimation.Play(this->AsShared(), true);
	//BorderPulseAnimation.Pause();

	ContentIntroAnimation.AddCurve(0.0f, TutorialConstants::ContentIntroAnimationLength, ECurveEaseFunction::Linear);
	ContentIntroAnimation.Play(this->AsShared());

	//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GWorld, 0);
	//ATutorialsPlayerController* aaa = Cast<ATutorialsPlayerController>(PlayerController);

	ChildSlot
	[
		SNew(SFxWidget)
		.Visibility(EVisibility::SelfHitTestInvisible)
		.RenderScaleOrigin(FVector2D(0.5f, 0.5f))
		[
			SNew(SOverlay)
			//.Visibility(this, &STutorialContent::GetVisibility)
			+ SOverlay::Slot()
			[
				SAssignNew(ContentWidget, SBorder)

				// Add more padding if the content is to be displayed centrally (i.e. not on a widget)
				//.Padding(bIsStandalone ? TutorialConstants::BorderSizeStandalone : TutorialConstants::BorderSize)
				//.Padding(TutorialConstants::BorderSize)
				//.Visibility(EVisibility::SelfHitTestInvisible)
				//.BorderImage(FVRSEditorStyle::GetBrush("Tutorials.Border"))
				.BorderBackgroundColor(this, &SVRSTutorialContent::GetBackgroundColor)
				//.ForegroundColor(FCoreStyle::Get().GetSlateColor("InvertedForeground"))
				[
					//SNew(SFxWidget)
					////.RenderScale(this, &SVRSTutorialContent::GetInverseAnimatedZoom)
					//.RenderScaleOrigin(FVector2D(0.5f, 0.5f))
					//[
					//	SNew(SVerticalBox)
					//	+ SVerticalBox::Slot()
					//	.AutoHeight()
					//	[
					//		SNew(SHorizontalBox)
					//		+ SHorizontalBox::Slot()
					//		.AutoWidth()
					//		.MaxWidth(600.0f)
					//		.VAlign(VAlign_Center)
							//[
								//GenerateContentWidget()
								GTutorialContentMgr->TutorialContentPanel->TakeWidget()
							//]
						//]
					 //]
				]
			]


			//+ SOverlay::Slot()
			//.VAlign(VAlign_Bottom)
			//.HAlign(HAlign_Left)
			//.Padding(12.0f)
			//[
			//	SAssignNew(BackButton, SButton)
			//	//.ToolTipText(this, &SVRSTutorialContent::GetBackButtonTooltip)
			//	//.OnClicked(this, &SVRSTutorialContent::HandleBackButtonClicked)
			//	////.Visibility(this, &SVRSTutorialContent::GetBackButtonVisibility)
			//	//.ButtonStyle(&FVRSEditorStyle::Get().GetWidgetStyle<FButtonStyle>("Tutorials.Content.NavigationButtonWrapper"))
			//	//.ContentPadding(0.0f)
			//	//[
			//	//	SNew(SBox)
			//	//	.Padding(8.0f)
			//	//	[
			//	//		SNew(SBorder)
			//	//		.BorderImage(this, &SVRSTutorialContent::GetBackButtonBorder)
			//	//		[
			//	//			SNew(SHorizontalBox)
			//	//			+ SHorizontalBox::Slot()
			//	//			.AutoWidth()
			//	//			[
			//	//				SNew(SImage)
			//	//				.Image(this, &SVRSTutorialContent::GetBackButtonBrush)
			//	//				.ColorAndOpacity(FLinearColor::White)
			//	//			]
			//	//		]
			//	//	]
			//	//]
			//]
			//+ SOverlay::Slot()
			//.VAlign(VAlign_Bottom)
			//.HAlign(HAlign_Right)
			//.Padding(12.0f)
			//[
			//	SAssignNew(NextButton, SButton)
			//	.OnClicked(this, &SVRSTutorialContent::HandleNextClicked)
			//	.ButtonStyle(&FVRSEditorStyle::Get().GetWidgetStyle<FButtonStyle>("Tutorials.Content.NavigationButtonWrapper"))
			//]
		]
	];
}

FVector2D SVRSTutorialContent::GetPosition() const
{
	return FVector2D();
}

FVector2D SVRSTutorialContent::GetSize() const
{
	return FVector2D();
}

void SVRSTutorialContent::HandlePaintNamedWidget(TSharedRef<SWidget> InWidget, const FGeometry& InGeometry)
{

}

void SVRSTutorialContent::HandleResetNamedWidget()
{

}

void SVRSTutorialContent::HandleCacheWindowSize(const FVector2D& InWindowSize)
{

}

void SVRSTutorialContent::GetAnimationValues(float& OutAlphaFactor, float& OutPulseFactor, FLinearColor& OutShadowTint, FLinearColor& OutBorderTint) const
{
	if (BorderIntroAnimation.IsPlaying())
	{
		OutAlphaFactor = BorderIntroAnimation.GetLerp();
		OutPulseFactor = (1.0f - OutAlphaFactor) * 50.0f;
		OutShadowTint = FLinearColor(1.0f, 1.0f, 0.0f, OutAlphaFactor);
		OutBorderTint = FLinearColor(1.0f, 1.0f, 0.0f, OutAlphaFactor * OutAlphaFactor);
	}
	else
	{
		float PulseAnimationProgress = BorderPulseAnimation.GetLerp();
		OutAlphaFactor = 1.0f - (0.5f + (FMath::Cos(2.0f * PI * PulseAnimationProgress) * 0.5f));
		OutPulseFactor = 0.5f + (FMath::Cos(2.0f * PI * PulseAnimationProgress) * 0.5f);
		OutShadowTint = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
		OutBorderTint = FLinearColor(1.0f, 1.0f, 0.0f, TutorialConstants::MinBorderOpacity + ((1.0f - TutorialConstants::MinBorderOpacity) * OutAlphaFactor));
	}
}

int32 SVRSTutorialContent::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	UE_LOG(LogTemp, Warning, TEXT("OnPaint"));


	CachedContentGeometry = AllottedGeometry;
	CachedContentGeometry.AppendTransform(FSlateLayoutTransform(OutDrawElements.GetWindow()->GetPositionInScreen()));

	{
		float AlphaFactor;
		float PulseFactor;
		FLinearColor ShadowTint;
		FLinearColor BorderTint;
		GetAnimationValues(AlphaFactor, PulseFactor, ShadowTint, BorderTint);

		const FSlateBrush* ShadowBrush = FCoreStyle::Get().GetBrush(TEXT("Tutorials.Shadow"));
		const FSlateBrush* BorderBrush = FCoreStyle::Get().GetBrush(TEXT("Tutorials.Border"));


		// OffsetFromParent  ParentAbsolutePosition  InLocalSize InScale
		//FGeometry Geom = FGeometry(FVector2D(12.f, 12.f), FVector2D(10.f, 76.f), FVector2D(311.f, 412.f), 1.f);
		//CachedGeometry = FGeometry(OffsetFromParent, ParentAbsolutePosition, InLocalSize, 1.f);
		//const FGeometry& WidgetGeometry = Geom;
		const FGeometry& WidgetGeometry = CachedGeometry;
		const FVector2D WindowSize = OutDrawElements.GetWindow()->GetSizeInScreen();

		// We should be clipped by the window size, not our containing widget, as we want to draw outside the widget
		FSlateRect WindowClippingRect(0.0f, 0.0f, WindowSize.X, WindowSize.Y);

		FPaintGeometry ShadowGeometry((WidgetGeometry.AbsolutePosition - FVector2D(ShadowBrush->Margin.Left, ShadowBrush->Margin.Top) * ShadowBrush->ImageSize * WidgetGeometry.Scale * TutorialConstants::ShadowScale),
			((WidgetGeometry.Size * WidgetGeometry.Scale) + (FVector2D(ShadowBrush->Margin.Right * 2.0f, ShadowBrush->Margin.Bottom * 2.0f) * ShadowBrush->ImageSize * WidgetGeometry.Scale * TutorialConstants::ShadowScale)),
			WidgetGeometry.Scale * TutorialConstants::ShadowScale);
		// draw highlight shadow
		FSlateDrawElement::MakeBox(OutDrawElements, LayerId++, ShadowGeometry, ShadowBrush, WindowClippingRect, ESlateDrawEffect::None, ShadowTint);

		FVector2D PulseOffset = FVector2D(PulseFactor * TutorialConstants::MaxBorderOffset, PulseFactor * TutorialConstants::MaxBorderOffset);

		FVector2D BorderPosition = (WidgetGeometry.AbsolutePosition - ((FVector2D(BorderBrush->Margin.Left, BorderBrush->Margin.Top) * BorderBrush->ImageSize * WidgetGeometry.Scale) + PulseOffset));
		FVector2D BorderSize = ((WidgetGeometry.Size * WidgetGeometry.Scale) + (PulseOffset * 2.0f) + (FVector2D(BorderBrush->Margin.Right * 2.0f, BorderBrush->Margin.Bottom * 2.0f) * BorderBrush->ImageSize * WidgetGeometry.Scale));

		FPaintGeometry BorderGeometry(BorderPosition, BorderSize, WidgetGeometry.Scale);

		// draw highlight border
		FSlateDrawElement::MakeBox(OutDrawElements, LayerId++, BorderGeometry, BorderBrush, WindowClippingRect, ESlateDrawEffect::None, BorderTint);


	}


	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyClippingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
}

TSharedRef<SWidget> SVRSTutorialContent::GenerateContentWidget()
{
	TArray< TSharedRef< class ITextDecorator > > Decorators;
	FText TmpText = FText::FromString(TEXT("The tools in the editor are made up of multiple panels.They can be moved around, docked, closed, etc.to create custom layouts.\
			If you ever hide something you need, all panels are accessible from the Window menu."));
	const bool bForEditing = false;
	//FTutorialText::GetRichTextDecorators(bForEditing, Decorators);

	TSharedRef<SRichTextBlock> TextBlock = SNew(SRichTextBlock)
		.Visibility(EVisibility::SelfHitTestInvisible)
		.TextStyle(FVRSEditorStyle::Get(), "Tutorials.Content.Text")
		.DecoratorStyleSet(&FVRSEditorStyle::Get())
		.Decorators(Decorators)
		.Text(TmpText)//.Text(InContent.Text)
		.AutoWrapText(false)
		.WrapTextAt(600.0f)//.WrapTextAt(WrapTextAt)
		.Margin(4)
		.LineHeightPercentage(1.1f)
		.HighlightText(TAttribute<FText>());

	return TextBlock;
}

FText SVRSTutorialContent::GetBackButtonTooltip() const
{
	if (IsBackEnabled.Get())
	{
		return LOCTEXT("BackButtonTooltip", "Go to the previous stage of this tutorial.");
	}
	return FText::GetEmpty();
}

FSlateColor SVRSTutorialContent::GetBackgroundColor() const
{
	// note cant use IsHovered() here because our widget is SelfHitTestInvisible
	const FVector2D CursorPos = FSlateApplication::Get().GetCursorPos();
	//return CachedContentGeometry.IsUnderLocation(CursorPos) ? FVRSEditorStyle::Get().GetColor("Tutorials.Content.Color.Hovered") : FVRSEditorStyle::Get().GetColor("Tutorials.Content.Color");
	return  FVRSEditorStyle::Get().GetColor("Tutorials.Content.Color");
}

FReply SVRSTutorialContent::HandleNextClicked()
{
	return FReply::Handled();
}

FReply SVRSTutorialContent::HandleBackButtonClicked()
{
	return FReply::Handled();
}

const FSlateBrush* SVRSTutorialContent::GetBackButtonBorder() const
{
	return BackButton->IsHovered() ? &FVRSEditorStyle::Get().GetWidgetStyle<FButtonStyle>("Tutorials.Content.NavigationBackButton").Hovered : &FVRSEditorStyle::Get().GetWidgetStyle<FButtonStyle>("Tutorials.Content.NavigationBackButton").Normal;
}

const FSlateBrush* SVRSTutorialContent::GetBackButtonBrush() const
{
	if (IsBackEnabled.Get())
	{
		return FVRSEditorStyle::GetBrush("Tutorials.Navigation.BackButton");
	}
	return FVRSEditorStyle::GetDefaultBrush();
}

EVisibility SVRSTutorialContent::GetBackButtonVisibility() const
{
	return IsBackEnabled.Get() == true ? EVisibility::Visible : EVisibility::Collapsed;
}

#undef LOCTEXT_NAMESPACE