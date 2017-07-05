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
	TmpContent.Content = TEXT("美国国家航空航天局6月30日宣布，一项防止小行星撞地球的计划已经从概念探讨阶段进入初步设计阶段，\
		研发完成的航天器将撞击一对小行星。这项计划名为“双小行星变轨测试”（DART），是美国航天局为防止小行星撞击地球设计的首个改变小行星轨道的技术验证项目，\
		将发射一颗航天器撞击名为“双子星”的一对小行星。");
	TArrayContent.Add(TmpContent);

	FPageContent TmpContent1;
	TmpContent1.Type = EPage::Continue;
	TmpContent1.Content = TEXT("这对小行星由“双子星A”和“双子星B”组成，前者直径大约780米，后者直径大约160米并且环绕前者飞行。");
	TArrayContent.Add(TmpContent1);

	FPageContent TmpContent2;
	TmpContent2.Type = EPage::Continue;
	TmpContent2.Content = TEXT("DART计划的航天器体积与一台电冰箱差不多，发射后将瞄准“双子星B”飞去，最终以每秒大约6千米的速率撞上这颗小行星。继而，研究人员将在地面观察这次碰撞，\
		研究碰撞将如何改变小行星的飞行轨道。“双小行星为这类测试提供了绝佳的天然实验室。”DART计划研究人员汤姆·施塔尔特说，“‘双子星B’环绕‘双子星A’飞行，\
		从而更易观察撞击效果，同时确保实验不会改变这一对小行星围绕太阳运行的轨道。”");
	TArrayContent.Add(TmpContent2);

	FPageContent TmpContent3;
	TmpContent3.Type = EPage::Continue;
	TmpContent3.Content = TEXT("DART的研究对象是中等体积小行星。它们一旦撞上地球，可造成“地区性破坏”，“双子星B”即属于这类天体。");
	TArrayContent.Add(TmpContent3);

	FPageContent TmpContent4;
	TmpContent4.Type = EPage::Botton;
	TmpContent4.Content = TEXT("美国航天局2016年组建“地球防御协调办公室”，职责包括发现、跟踪和辨别对地球构成潜在威胁的小行星和彗星，并就可能的碰撞发布预警。");
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
