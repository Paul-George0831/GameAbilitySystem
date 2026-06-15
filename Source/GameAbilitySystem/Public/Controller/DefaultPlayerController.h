#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

class UDamageTextComponent;
class USplineComponent;
class UGASAbilitySystemComponentBase;
struct FGameplayTag;
class UInputConfigDataAsset;
struct FInputActionValue;
class UInputAction;
class IHighlightInterface;

UCLASS()
class GAMEABILITYSYSTEM_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADefaultPlayerController();
	void AutoRun();

	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float Damage, ACharacter* TargetCharacter);
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	//移动函数，接受一个输入动作值
	void Move(const FInputActionValue& Value);
	
	UPROPERTY(BlueprintReadWrite)
	bool bAutoRunning = false;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
	
private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<class UInputMappingContext> DefaultPlayerContext;

	void ShiftPressed(const FInputActionValue& Value) { bShiftPressed = true; };
	
	void ShiftReleased(const FInputActionValue& Value) { bShiftPressed = false; };
	
	bool bShiftPressed = false;
	
	//移动输入
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;
	
	void CursorTrace();

	TObjectPtr<IHighlightInterface> LastHighLightedActor;

	TObjectPtr<IHighlightInterface> CurHighLightActor;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputConfigDataAsset> InputConfig;
	
	FVector CachedDestination = FVector(0.0f);
	
	float FollowTime = 0.0f;
	
	float ShortThreshold = 0.5f;
	
	
	bool bTargeting = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float AutoRunAcceptanceRadius = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<USplineComponent> Spline;
	
	FHitResult CursorHit;
	
	/*GA Input*/
	UPROPERTY()
	TObjectPtr<UGASAbilitySystemComponentBase> _GASASC;
	
	UGASAbilitySystemComponentBase* GetASC();
	
	void AbilityInputTagPressed(FGameplayTag InputTag);//不能传引用
	
	void AbilityInputTagReleased(FGameplayTag InputTag);
	
	void AbilityInputTagHeld(FGameplayTag InputTag);
	/*End*/
};
