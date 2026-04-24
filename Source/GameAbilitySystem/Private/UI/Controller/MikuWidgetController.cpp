// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Controller/MikuWidgetController.h"

void UMikuWidgetController::SetWidgetControllerParams(const FMikuWidgetControllerParams& params)
{
	_AbilitySystemComponent = params._AbilitySystemComponent;
	_AttributeSet = params._AttributeSet;
	_PlayerController = params._PlayerController;
	_PlayerState = params._PlayerState;
}

void UMikuWidgetController::BroadcastInitialValues()
{
}

void UMikuWidgetController::BindCallbacksToDependencies()
{
}
