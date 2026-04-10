#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;

UCLASS()
class GAMEABILITYSYSTEM_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADefaultPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	//������ǿ�������
	virtual void SetupInputComponent() override;

	//移动函数，接受一个输入动作值
	void Move(const FInputActionValue& Value);
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> DefaultPlayerContext;

	//移动输入
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void CursorTrace();

	TObjectPtr<class IHighlightInterface> LastHighLightedActor;

	TObjectPtr<class IHighlightInterface> CurHighLightActor;
};
