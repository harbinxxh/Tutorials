
#include "Tutorials.h"
#include "VRSDetail.h"
#include "SDetailWidget.h"
#include "TutorialsPlayerController.h"

//void FDetailBuilder::AddEntryBlock(EWidgetType::Type Type, const FText& InText, const FOnCheckStateChanged& InOnCheckStateChanged)
//{
//	TSharedRef< FDetailEntryBlock > DetailEntryBlock( new FDetailEntryBlock(Type, InText, InOnCheckStateChanged) );
//	DetailBuilderList.Add(DetailEntryBlock);
//}


//TSharedRef< class SWidget > FDetailBuilder::MakeWidget()
//{
//
//
//	TSharedRef<SWidget> DetailWidget = SNew(SDetailWidget);
//
//	//			SNew(SButton)
//	//			.OnClicked(FOnClicked::CreateUObject(this, &ATutorialsPlayerController::HideTutorial))
//	//			.Content()
//	//			[
//	//				SNew(STextBlock)
//	//				.Text(FText::FromString(TEXT("隐藏新手引导")))
//	//			]
//
//
//
//	return DetailWidget;
//}






TSharedRef<SWidget> FVRSDetail::MakeDetailWidget()
{
	//TArray< TSharedRef< const FDetailBuilder > > DetailBuderList;


	// TSharedRef< FMenuEntryBlock > NewMenuEntryBlock( new FMenuEntryBlock( 

	//FDetailBuilder DetailBuilder;
	//DetailBuilder.AddEntryBlock(
	//	EWidgetType::WT_TEXTBLOCK_CHECK,
	//	FText::FromString(TEXT(""),
	//	FOnCheckStateChanged::BindUObject(&ATutorialsPlayerController::OnCheckStateChangedEvent)
	//)



	return SNew(SWindow);
}