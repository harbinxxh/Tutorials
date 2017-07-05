// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "VRSTutorialContentMgr.generated.h"

class UVRSWidgetTutorialContentPanel;
class SVRSTutorialContent;

UENUM()
namespace EContent
{
	enum Type
	{
		Top,
		Continue,
		Bottom
	};
}


USTRUCT()
struct FTutorialContenVRS
{
	GENERATED_USTRUCT_BODY()

	EContent::Type Type;
	FString Content;
};


/**
 * 
 */
UCLASS()
class UVRSTutorialContentMgr : public UObject
{
	GENERATED_BODY()
	
public:
	UVRSTutorialContentMgr();

	void Init();
	void ShowTutorial();
	void OnBack();
	void OnNext();


	int32 CurrentPage;
	int32 TotalPage;

	TArray<FTutorialContenVRS> TArrayContent;
	UVRSWidgetTutorialContentPanel* TutorialContentPanel;
	TSharedPtr<SVRSTutorialContent> VRSTutorialContent;
};

extern UVRSTutorialContentMgr * GTutorialContentMgr;
