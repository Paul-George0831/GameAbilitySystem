// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/CharacterClassInfo.h"

FCharacterClassDefaultInfo UCharacterClassInfo::FindClassDefaultInfo(ECharacterClass InClass)
{
	return CharacterClassInfoMap.FindChecked(InClass);
}
