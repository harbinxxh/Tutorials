// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "UMGTutorial.h"
#include "VRSTutorialWindow.h"

void UUMGTutorial::WidgetConstruct(
	UTextBlock * _TextBlock_Content,
	UButton* _BTN_Back,
	UButton* _BTN_Next
)
{
	TextBlock_Content = _TextBlock_Content;
	BTN_Back = _BTN_Back;
	BTN_Next = _BTN_Next;

	BTN_Back->OnClicked.AddDynamic(GTutorialWindow, &UVRSTutorialWindow::Callback_BackClicked);
	BTN_Next->OnClicked.AddDynamic(GTutorialWindow, &UVRSTutorialWindow::Callback_NextClicked);

}

void UUMGTutorial::Init(FPageContent& _PageContent)
{
	TextBlock_Content->SetText(FText::FromString(_PageContent.Content));

	if (_PageContent.Type == EPage::Top)
	{
		BTN_Back->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (_PageContent.Type == EPage::Continue)
	{
		BTN_Back->SetVisibility(ESlateVisibility::Visible);
		BTN_Next->SetVisibility(ESlateVisibility::Visible);
	}
	else if (_PageContent.Type == EPage::Botton)
	{
		BTN_Next->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UUMGTutorial::Show(bool _bSHow)
{
	if (_bSHow)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}
