// Fill out your copyright notice in the Description page of Project Settings.

//#include "VRS.h"
#include "Tutorials.h"
#include "VRSTutorialContentMgr.h"
#include "VRSWidgetTutorialConTentPanel.h"

UVRSTutorialContentMgr * GTutorialContentMgr = nullptr;

UVRSTutorialContentMgr::UVRSTutorialContentMgr()
{
	GTutorialContentMgr = this;
	CurrentPage = 0;
	TotalPage = 0;
}

void UVRSTutorialContentMgr::Init()
{
	FTutorialContenVRS TmpContent;
	TmpContent.Type = EContent::Top;
	TmpContent.Content = TEXT("The instructions on this page are for running the engine  \
		with projects compiled in a Development build configuration.\n You can substitute the \
		UE4Editor-*.exe or UE4-*.exe that you need for opening projects built in other configurations.\
		More information on the binary naming convention can be found on the Building Unreal Engine page.");
	TArrayContent.Add(TmpContent);
	
	FTutorialContenVRS TmpContent1;
	TmpContent1.Type = EContent::Continue;
	TmpContent1.Content = TEXT("You can add the -debug switch to force the executable to load the debug \
		\n version of the modules for your project, which contain all of the debugging symbols.");
	TArrayContent.Add(TmpContent1);

	FTutorialContenVRS TmpContent2;
	TmpContent2.Type = EContent::Continue;
	TmpContent2.Content = TEXT("From a command prompt, navigate to your \n [LauncherInstall][VersionNumber]\\Engine\\Binaries\\Win64 directory.");
	TArrayContent.Add(TmpContent2);

	FTutorialContenVRS TmpContent3;
	TmpContent3.Type = EContent::Continue;
	TmpContent3.Content = TEXT("Running the Editor From the Executable\n Navigate to your \n [LauncherInstall][VersionNumber]\\Engine\\Binaries\\Win64 directory.");
	TArrayContent.Add(TmpContent3);

	FTutorialContenVRS TmpContent4;
	TmpContent4.Type = EContent::Bottom;
	TmpContent4.Content = TEXT("Right-click on the UE4Editor.exe executable and choose Create shortcut.");
	TArrayContent.Add(TmpContent4);

	TotalPage = TArrayContent.Num();
}

void UVRSTutorialContentMgr::ShowTutorial()
{
	if (TutorialContentPanel->IsVisible())
	{
		TutorialContentPanel->ShowPanel(false);
	}
	else
	{
		CurrentPage = 0;
		TutorialContentPanel->ShowPanel(true);
		TutorialContentPanel->Init(TArrayContent[CurrentPage]);
	}
}

void UVRSTutorialContentMgr::OnBack()
{
	UE_LOG(LogTemp, Warning, TEXT("OnBack()"));
	if (CurrentPage != 0)
	{
		CurrentPage--;
		TutorialContentPanel->Init(TArrayContent[CurrentPage]);
	}
}

void UVRSTutorialContentMgr::OnNext()
{
	UE_LOG(LogTemp, Warning, TEXT("OnNext()"));

	if (CurrentPage < TotalPage -1)
	{
		CurrentPage++;
		TutorialContentPanel->Init(TArrayContent[CurrentPage]);
	}

}
