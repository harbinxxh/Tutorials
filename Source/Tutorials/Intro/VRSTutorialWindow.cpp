// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorials.h"
#include "UMG.h"
#include "VRSTutorialWindow.h"
#include "SBorderPulseAnimation.h"
#include "UMGTutorial.h"

UVRSTutorialWindow * GTutorialWindow = nullptr;

UVRSTutorialWindow::UVRSTutorialWindow()
{
	GTutorialWindow = this;
	TutorialWindow = nullptr;
	UserWidget = nullptr;
	CurrentPage = 0;
	TotalPage = 0;
}

void UVRSTutorialWindow::Init()
{

	FPageContent TmpContent;
	TmpContent.Type = EPage::Top;
	TmpContent.Content = TEXT("�������Һ��պ����6��30��������һ���ֹС����ײ����ļƻ��Ѿ��Ӹ���̽�ֽ׶ν��������ƽ׶Σ�\
		�з���ɵĺ�������ײ��һ��С���ǡ�����ƻ���Ϊ��˫С���Ǳ����ԡ���DART���������������Ϊ��ֹС����ײ��������Ƶ��׸��ı�С���ǹ���ļ�����֤��Ŀ��\
		������һ�ź�����ײ����Ϊ��˫���ǡ���һ��С���ǡ�");
	TArrayContent.Add(TmpContent);

	FPageContent TmpContent1;
	TmpContent1.Type = EPage::Continue;
	TmpContent1.Content = TEXT("���С�����ɡ�˫����A���͡�˫����B����ɣ�ǰ��ֱ����Լ780�ף�����ֱ����Լ160�ײ��һ���ǰ�߷��С�");
	TArrayContent.Add(TmpContent1);

	FPageContent TmpContent2;
	TmpContent2.Type = EPage::Continue;
	TmpContent2.Content = TEXT("DART�ƻ��ĺ����������һ̨������࣬�������׼��˫����B����ȥ��������ÿ���Լ6ǧ�׵�����ײ�����С���ǡ��̶����о���Ա���ڵ���۲������ײ��\
		�о���ײ����θı�С���ǵķ��й������˫С����Ϊ��������ṩ�˾��ѵ���Ȼʵ���ҡ���DART�ƻ��о���Ա��ķ��ʩ������˵������˫����B�����ơ�˫����A�����У�\
		�Ӷ����׹۲�ײ��Ч����ͬʱȷ��ʵ�鲻��ı���һ��С����Χ��̫�����еĹ������");
	TArrayContent.Add(TmpContent2);

	FPageContent TmpContent3;
	TmpContent3.Type = EPage::Continue;
	TmpContent3.Content = TEXT("DART���о��������е����С���ǡ�����һ��ײ�ϵ��򣬿���ɡ��������ƻ�������˫����B���������������塣");
	TArrayContent.Add(TmpContent3);

	FPageContent TmpContent4;
	TmpContent4.Type = EPage::Botton;
	TmpContent4.Content = TEXT("���������2016���齨���������Э���칫�ҡ���ְ��������֡����ٺͱ��Ե��򹹳�Ǳ����в��С���Ǻ����ǣ����Ϳ��ܵ���ײ����Ԥ����");
	TArrayContent.Add(TmpContent4);

	TotalPage = TArrayContent.Num();


	TSubclassOf<UUMGTutorial> WidgetClass = LoadClass<UUMGTutorial>(nullptr, TEXT("/Game/BP/BP_UMGTutorial.BP_UMGTutorial_C"));
	if (WidgetClass)
	{
		UserWidget = CreateWidget<UUMGTutorial>(GWorld, WidgetClass);
	}

	FGeometry Geom = FGeometry(FVector2D(12.f, 12.f), FVector2D(10.f, 76.f), FVector2D(311.f, 412.f), 1.f);

	SAssignNew(TutorialWindow, SWindow)
		.Title(FText::FromString(TEXT("Totorial")))
		//.SizingRule(ESizingRule::Autosized)
		.ClientSize(FVector2D(1280, 800))
		.AutoCenter(EAutoCenter::PreferredWorkArea)
		.SupportsMinimize(false)
		.SupportsMaximize(false)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SAssignNew(BorderPulseAnimation, SBorderPulseAnimation, Geom)
			]
			+ SOverlay::Slot()
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					UserWidget->TakeWidget()
				]
			]
		];

	FSlateApplication::Get().AddWindow(TutorialWindow.ToSharedRef());

	ShowTutorial(false);
	ShowBorderPulse(false);
}

void UVRSTutorialWindow::ShowTutorial(bool _bShow)
{
	if (_bShow)
	{
		UserWidget->Init(TArrayContent[CurrentPage]);
		UserWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		UserWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UVRSTutorialWindow::ShowBorderPulse(bool _bShow)
{
	if (_bShow)
	{
		BorderPulseAnimation->SetVisibility(EVisibility::Visible);
	}
	else
	{
		BorderPulseAnimation->SetVisibility(EVisibility::Hidden);
	}
}

void UVRSTutorialWindow::Callback_BackClicked()
{
	if (CurrentPage != 0)
	{
		CurrentPage--;
		UserWidget->Init(TArrayContent[CurrentPage]);
	}
}

void UVRSTutorialWindow::Callback_NextClicked()
{
	if (CurrentPage < TotalPage - 1)
	{
		CurrentPage++;
		UserWidget->Init(TArrayContent[CurrentPage]);
	}
}

void UVRSTutorialWindow::SetBorderPulseAnimation(FGeometry& InGeometry)
{
	BorderPulseAnimation->SetBorderPulsePosition(InGeometry);
}
