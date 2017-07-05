// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

/**
* The widget which displays 'floating' content
*/
class SBorderPulseAnimation : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SBorderPulseAnimation)
	{
		_Visibility = EVisibility::SelfHitTestInvisible;
	}
	
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, FGeometry& InGeometry);

	/** Handle repositioning the widget */
	FVector2D GetPosition() const;

	/** Handle resizing the widget */
	FVector2D GetSize() const;

	void SetBorderPulsePosition(FGeometry& InGeometry);

	/** Helper to determine the proper animation values for the border pulse */
	void GetAnimationValues(float& OutAlphaFactor, float& OutPulseFactor, FLinearColor& OutShadowTint, FLinearColor& OutBorderTint) const;

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

private:

	/** Reference to the canvas we use to position our content widgets */
	TSharedPtr<SCanvas> OverlayCanvas;

	/** Copy of the geometry our widget was last drawn with */
	FGeometry CachedGeometry;

	/** Copy of the geometry our content was last drawn with */
	mutable FGeometry CachedContentGeometry;

	/** Container for widget content */
	TSharedPtr<SWidget> ContentWidget;

	/** Attribute controlling enabled state of back functionality */
	TAttribute<bool> IsBackEnabled;

	/** Animation curves for displaying border */
	FCurveSequence BorderPulseAnimation;
	FCurveSequence BorderIntroAnimation;

	/** Animation curve for displaying content */
	FCurveSequence ContentIntroAnimation;


	/** Back button widget */
	TSharedPtr<SWidget> BackButton;

	/** Next button widget */
	TSharedPtr<SWidget> NextButton;

};