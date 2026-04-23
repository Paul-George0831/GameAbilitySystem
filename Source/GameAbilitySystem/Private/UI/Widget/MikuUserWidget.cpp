// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MikuUserWidget.h"

void UMikuUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
