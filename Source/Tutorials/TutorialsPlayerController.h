// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "SVRSTutorialRoot.h"
#include "SVRSTutorialContent.h"
#include "TutorialsPlayerController.generated.h"

//class UUserWidget;

/**
 * 
 */
UCLASS()
class TUTORIALS_API ATutorialsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	TSharedPtr<SVRSTutorialRoot> TutorialRoot;
	TSharedPtr<SVRSTutorialContent> TutorialContent;

	FReply ShowTutorial();
	FReply HideTutorial();
	FReply SetBorderPulsePosition();

	/** Reference to the canvas we use to position our content widgets */
	TSharedPtr<SCanvas> OverlayCanvas;

	// SCustomWidget Delegate Function
	void OnSpinBoxValueChangedEvent(float InValue);
	void OnCheckStateChangedEvent( ECheckBoxState InNewState);
	float OnGetSpinBoxValueEvent();
	ECheckBoxState OnGetCheckBoxStateEvent();
	FLinearColor OnGetLinearColorEvent();
	void OnLinearColorValueChangedEvent(FLinearColor InLinearColor);
	void OnComboBoxSelectionChanged(const FString& SelectItemName);

	float TestSpinBoxValue;
	ECheckBoxState TestCheckBoxState;
	FLinearColor TestColor;


	/////////////////

	//TSharedRef<SWidget> MakeDetailWidget();

	void OnButtonClicked();


};
