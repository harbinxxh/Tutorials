// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "VRSTutorialWindow.generated.h"

class SBorderPulseAnimation;
class UUMGTutorial;

UENUM()
namespace EPage
{
	enum Type
	{
		Top,
		Continue,
		Botton
	};
}

USTRUCT()
struct FPageContent
{
	GENERATED_USTRUCT_BODY()

	EPage::Type Type;
	FString Content;
};

/**
 * 
 */
UCLASS()
class TUTORIALS_API UVRSTutorialWindow : public UObject
{
	GENERATED_BODY()

public:
	UVRSTutorialWindow();
	
	void Init();
	void ShowTutorial(bool _bShow);
	void ShowBorderPulse(bool _bShow);

	int32 CurrentPage;
	int32 TotalPage;

	TArray<FPageContent> TArrayContent;
	TSharedPtr<SWindow> TutorialWindow;
	TSharedPtr<SBorderPulseAnimation> BorderPulseAnimation;
	UUMGTutorial* UserWidget;

	UFUNCTION()
	void Callback_BackClicked();
	UFUNCTION()
	void Callback_NextClicked();

	void SetBorderPulseAnimation(FGeometry& InGeometry);
};

extern UVRSTutorialWindow * GTutorialWindow;