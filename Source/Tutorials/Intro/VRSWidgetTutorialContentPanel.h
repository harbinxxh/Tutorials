// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "VRSTutorialContentMgr.h"
#include "VRSWidgetTutorialContentPanel.generated.h"

/**
 * 
 */
UCLASS()
class UVRSWidgetTutorialContentPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "WidgetTutorialContentPanel")
	void WidgetConstruct(
		UTextBlock* _TextBlock_Content,
		UButton* _BTN_Back,
		UButton* _BTN_Next
	);
	
	UTextBlock* TextBlock_Content;
	UButton* BTN_Back;
	UButton* BTN_Next;

	void Init(FTutorialContenVRS& _TutorialContent);
	void ShowPanel(bool _bShow);

	UFUNCTION()
	void OnBack();
	UFUNCTION()
	void OnNext();

};
