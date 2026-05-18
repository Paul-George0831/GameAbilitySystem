// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/AttributeInfo.h"

//通过传入的Tag找到AttributeValue，AttributeDescription，AttributeName，AttributeTag
FAuraAttributeInfo UAttributeInfo::FindAttributeByTag(const FGameplayTag& AttributeTag, bool bLogNotFind) const
{
	for (const FAuraAttributeInfo& AttributeInfo : AttributeInfos)
	{
		if (AttributeInfo.AttributeTag == AttributeTag)
		{
			return AttributeInfo;
		}
	}
	if (bLogNotFind)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Find Target AttributeInfo"))
	}
	return FAuraAttributeInfo();
}
