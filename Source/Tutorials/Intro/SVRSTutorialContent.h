// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

//#include "IDocumentation.h"
//#include "IDocumentationPage.h"
//#include "EditorTutorial.h"
//#include "STutorialOverlay.h"
//#include "SVRSTutorialContent.generated.h"

#include "SVRSTutorialOverlay.h"

/**
* The widget which displays 'floating' content
*/
class SVRSTutorialContent : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SVRSTutorialContent)
	{
		_Visibility = EVisibility::SelfHitTestInvisible;
		_IsStandalone = false;
	}







	/** Alignment of content relative to widget, note "Fill" is not supported */
	SLATE_ATTRIBUTE(EVerticalAlignment, VAlign)

	/** Alignment of content relative to widget, note "Fill" is not supported */
	SLATE_ATTRIBUTE(EHorizontalAlignment, HAlign)

	/** Offset form the widget we annotate */
	SLATE_ATTRIBUTE(FVector2D, Offset)

	/** Whether this a standalone widget (with its own close button) or part of a group of other widgets, paired with tutorial navigation */
	SLATE_ARGUMENT(bool, IsStandalone)

	/** Delegate fired when the close button is clicked */
	SLATE_EVENT(FSimpleDelegate, OnClosed)

	/** Delegate fired when the back button is clicked */
	SLATE_EVENT(FSimpleDelegate, OnBackClicked)

	/** Delegate fired when the home button is clicked */
	SLATE_EVENT(FSimpleDelegate, OnHomeClicked)

	/** Delegate fired when the next button is clicked */
	SLATE_EVENT(FSimpleDelegate, OnNextClicked)

	/** Attribute controlling enabled state of back functionality */
	SLATE_ATTRIBUTE(bool, IsBackEnabled)

	/** Attribute controlling enabled state of home functionality */
	SLATE_ATTRIBUTE(bool, IsHomeEnabled)

	/** Attribute controlling enabled state of next functionality */
	SLATE_ATTRIBUTE(bool, IsNextEnabled)

	/** Where text should be wrapped */
	SLATE_ARGUMENT(float, WrapTextAt)

	/** Anchor if required */
	//SLATE_ARGUMENT(FTutorialContentAnchor, Anchor)

	/** Whether we can show full window content in this overlay (i.e. in the same window as the navigation controls) */
	SLATE_ARGUMENT(bool, AllowNonWidgetContent)

	/** Delegate for querying whether a widget was drawn */
	SLATE_EVENT(FOnWasWidgetDrawn, OnWasWidgetDrawn)

	/** Text to display on next/home button */
	SLATE_ATTRIBUTE(FText, NextButtonText)

	/** Text to display on back button */
	SLATE_ATTRIBUTE(FText, BackButtonText)

	SLATE_END_ARGS()

	//void Construct(const FArguments& InArgs, UVRSEditorTutorial* InTutorial, const FTutorialContent& InContent);
	void Construct(const FArguments& InArgs, FGeometry& InGeometry);

	/** Handle repositioning the widget */
	FVector2D GetPosition() const;

	/** Handle resizing the widget */
	FVector2D GetSize() const;

	/** Delegate handler called back from the overlay paint routines to flag whether we should paint as well (i.e. if this widget content is highlighted for the current stage) */
	void HandlePaintNamedWidget(TSharedRef<SWidget> InWidget, const FGeometry& InGeometry);

	/** Called back from the overlay paint routines to reset the flag we check for painting with */
	void HandleResetNamedWidget();

	/** Handle caching window size - called back from overlay paint routine */
	void HandleCacheWindowSize(const FVector2D& InWindowSize);


	/** Helper to determine the proper animation values for the border pulse */
	void GetAnimationValues(float& OutAlphaFactor, float& OutPulseFactor, FLinearColor& OutShadowTint, FLinearColor& OutBorderTint) const;

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyClippingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	/** Helper function to generate widgets from an FTutorialContent struct */
	static TSharedRef<SWidget> GenerateContentWidget();

	// XXH
	/** Delegate handler allowing us to change the tootlip of the 'back' button depending on context */
	FText GetBackButtonTooltip() const;

	/** Alter the background color depending on hover state */
	FSlateColor GetBackgroundColor() const;

	/** Delegate handler for going to the next stage of the tutorial (From button) */
	FReply HandleNextClicked();

	/** Delegate handler for going to the previous stage of the tutorial (From button) */
	FReply HandleBackButtonClicked();

	/** We need to override the border ourselves, rather than let the button handle it, as we are using a larger apparent hitbox */
	const FSlateBrush* GetBackButtonBorder() const;

	/** Delegate handler allowing us to change the brush of the 'back' button depending on context */
	const FSlateBrush* GetBackButtonBrush() const;

	/* Get the visibilty of the back button */
	EVisibility GetBackButtonVisibility() const;

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