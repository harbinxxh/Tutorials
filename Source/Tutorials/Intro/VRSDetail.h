// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SDetailWidget.h"

//UENUM()
//namespace EWidgetType
//{
//	enum Type
//	{
//		WT_BUTTON,
//		WT_TEXTBLOCK_BUTTON,
//		WT_TEXTBLOCK_CHECK,
//	};
//}
//
//
//class FDetailEntryBlock
//{
//public:
//	FDetailEntryBlock()
//	{}
//
//	FDetailEntryBlock(EWidgetType::Type& InType, const FText& InText, const FOnCheckStateChanged& InOnCheckStateChanged)
//		: Type(InType), Text(InText), OnCheckStateChanged(InOnCheckStateChanged)
//	{
//	}
//
//	EWidgetType::Type Type; // 控件类型
//
//	FText Text;				// 文本描述
//
//	/** Delegate Check*/
//	FOnCheckStateChanged OnCheckStateChanged;
//};
//
//
//class FDetailBuilder
//{
//public:
//
//	void AddEntryBlock(EWidgetType::Type Type, const FText& InText, const FOnCheckStateChanged& InOnCheckStateChanged)
//	{
//		TSharedRef< FDetailEntryBlock > DetailEntryBlock(new FDetailEntryBlock(Type, InText, InOnCheckStateChanged));
//		DetailBuilderList.Add(DetailEntryBlock);
//	}
//
//
//	TSharedRef< class SWidget > MakeWidget()
//	{
//
//		TSharedRef<SWidget> DetailWidget = SNew(SDetailWidget);
//		return DetailWidget;
//	}
//
//	TArray< TSharedRef < const FDetailEntryBlock > > DetailBuilderList;
//};





class FVRSDetail
{
public:


	static TSharedRef<SWidget> MakeDetailWidget();


};