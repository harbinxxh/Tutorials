
#include "Tutorials.h"
#include "Runtime/Analytics/Analytics/Public/Interfaces/IAnalyticsProvider.h"
#include "VRSEditorStyleSet.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "SBorderPulseAnimation.h"

#define LOCTEXT_NAMESPACE "SBorderPulseAnimation"

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

void SBorderPulseAnimation::Construct(const FArguments& InArgs, FGeometry& InGeometry)
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

	ChildSlot
	[
		SNullWidget::NullWidget
	];
}

FVector2D SBorderPulseAnimation::GetPosition() const
{
	return FVector2D();
}

FVector2D SBorderPulseAnimation::GetSize() const
{
	return FVector2D();
}

void SBorderPulseAnimation::SetBorderPulsePosition(FGeometry& InGeometry)
{
	CachedGeometry = InGeometry;
}

void SBorderPulseAnimation::GetAnimationValues(float& OutAlphaFactor, float& OutPulseFactor, FLinearColor& OutShadowTint, FLinearColor& OutBorderTint) const
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

int32 SBorderPulseAnimation::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
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

#undef LOCTEXT_NAMESPACE