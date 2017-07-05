// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "UMG.h"
#include "VRSWidgetTutorialContentPanel.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"


void UVRSWidgetTutorialContentPanel::WidgetConstruct(
	UTextBlock* _TextBlock_Content,
	UButton* _BTN_Back,
	UButton* _BTN_Next
)
{
	TextBlock_Content = _TextBlock_Content;
	BTN_Back = _BTN_Back;
	BTN_Next = _BTN_Next;
	BTN_Back->OnClicked.AddDynamic(this, &UVRSWidgetTutorialContentPanel::OnBack);
	BTN_Next->OnClicked.AddDynamic(this, &UVRSWidgetTutorialContentPanel::OnNext);
}

void UVRSWidgetTutorialContentPanel::Init(FTutorialContenVRS& _TutorialContent)
{
	TextBlock_Content->SetText(FText::FromString(_TutorialContent.Content));
}

void UVRSWidgetTutorialContentPanel::ShowPanel(bool _bShow)
{
	if (_bShow)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UVRSWidgetTutorialContentPanel::OnBack()
{
	GTutorialContentMgr->OnBack();
}

void UVRSWidgetTutorialContentPanel::OnNext()
{
	GTutorialContentMgr->OnNext();
}
