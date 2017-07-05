// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "VRSTutorialWindow.h"
#include "UMGTutorial.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIALS_API UUMGTutorial : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UMGTutorial")
		void WidgetConstruct(
			UTextBlock * _TextBlock_Content,
			UButton* _BTN_Back,
			UButton* _BTN_Next
		);
	
	void Init(FPageContent& _PageContent);
	void Show(bool _bSHow);

	UTextBlock* TextBlock_Content;
	UButton* BTN_Back;
	UButton* BTN_Next;

};
