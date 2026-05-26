// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TargetDataUnderCursor.h"

#include "AbilitySystemComponent.h"

UTargetDataUnderCursor* UTargetDataUnderCursor::CreateTargetDataUnderCursor(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderCursor* Obj = NewAbilityTask<UTargetDataUnderCursor>(OwningAbility);
	return Obj;
}

void UTargetDataUnderCursor::Activate()
{
	Super::Activate();
	if (Ability->IsLocallyControlled())
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataUnderCursor::OnTargetDataReplicatedCallback);
		/*CallReplicatedTargetDataDelegatesIfSet 会检查是否有 TargetData 已经被复制过来了并且还未被消费。如果已经有数据了，它会立即广播委托（触发上面的回调）；
		 *如果还没有数据即CallReplicatedTargetDataDelegatesIfSet返回false，则调用SetWaitingOnRemotePlayerData() 将 Ability Task 标记为"等待远程数据"状态 — 此时 Task 不会完成，而是挂起等待客户端发来的数据
		 */
		if (!AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, ActivationPredictionKey))
		{
			SetWaitingOnRemotePlayerData();//OnTargetDataReplicatedCallback的ConsumeClientReplicatedTargetData会取消挂起
		}
	}
}

void UTargetDataUnderCursor::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	FHitResult HitResult;
	const FGameplayAbilityActorInfo* AbilityActorInfo = Ability->GetCurrentActorInfo();
	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	AbilityActorInfo->PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false, HitResult);
	Data->HitResult = HitResult;
	DataHandle.Add(Data);
	//DataHandle打包给服务器
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle, FGameplayTag(),AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderCursor::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivateTag)
{	
	//消费（清理）”客户端已经复制给服务器的目标数据
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());//通知ASC已经接收到了Data，需要传入当前技能的句柄和原始预测键
	if (ShouldBroadcastAbilityTaskDelegates())//防止网络同步异常访问空指针
	{
		ValidData.Broadcast(DataHandle);
	}
}
