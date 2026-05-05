#include "UI/HUD/MikuHUD.h"
#include "UI/Widget/MikuUserWidget.h"
#include "UI/Controller/MikuWidgetController.h"
#include "UI/Controller/OverlayWidgetController.h"
#include "Blueprint/UserWidget.h"

UOverlayWidgetController* AMikuHUD::GetOverlayWidgetController(const FMikuWidgetControllerParams& params)//初始化overlaywidgetcontroller和获取都写在这里面了
{
	//如果OverlayWidgetController为空，直接创建一个OverlayWidgetController
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass); //依赖倒置，如果OverlayWidgetController需要蓝图写一些额外逻辑，如果不使用OverlayWidgetControllerClass就无法让c++得知蓝图的逻辑
		//outer父级对象，设计GC系统；class要创建对象的类型；
		OverlayWidgetController->SetWidgetControllerParams(params);
		OverlayWidgetController->BindCallbacksToDependencies();//一旦创建好了OverlayWidgetController,就应该绑定回调函数
	}
	return OverlayWidgetController;
}

void AMikuHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass,TEXT("OverlayWidgetClass is not found"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not found"));
	
	//为什么使用UUerWidget然后再强转？
	//解耦代码，如果后续overwidgetclass改成别的类了，那么如果直接再createwidget显式传递模板强转大概率不成功，那么这样先createwidget再强转就可以获取修改后的类型。第二就是如果UMikuwidget如果有蓝图代码，如果直接使用staticclass就无法获取蓝图代码
	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayUserWidget = Cast<UMikuUserWidget>(UserWidget);
	
	const FMikuWidgetControllerParams params(PC, PS, ASC, AS);
	
	UOverlayWidgetController* OverlayController = GetOverlayWidgetController(params);//方便逻辑，存一个本地变量
	
	OverlayUserWidget->SetWidgetController(OverlayController);
	OverlayController->BroadcastInitialValues();//在GetOverlayWidgetController就已经初始化类内overlaywidgetcontroller了，这里无需继续赋值overlaywidgetcontroller
	
	OverlayUserWidget->AddToViewport();
}
