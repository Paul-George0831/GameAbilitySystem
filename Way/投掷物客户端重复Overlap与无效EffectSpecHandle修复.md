# 投掷物客户端重复 Overlap 与无效 DamageEffectSpecHandle 修复

## 问题描述

客户端发动火球攻击时，单个投掷物触发多次 Overlap 事件：
- 第一次 Overlap 的 `DamageEffectSpecHandle` 有效
- 随后几次 Overlap 的 `DamageEffectSpecHandle` 无效
- 全局只创建了一个火球实例

## 根因分析

问题由两个独立原因叠加导致：

### 1. 自伤检查依赖不入网的 `FGameplayEffectSpecHandle`

`AuraProjectile.h:26`：
```cpp
UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
FGameplayEffectSpecHandle DamageEffectSpecHandle;
```

- `ExposeOnSpawn` 仅在服务端 `SpawnActor` 时生效
- `FGameplayEffectSpecHandle` 内部是 `TSharedPtr`，**不可网络复制**
- 客户端投掷物 Actor 复制后，`DamageEffectSpecHandle` 为空
- 原有的自伤检查（通过 `EffectCauser`）在客户端完全跳过，无法阻止对施法者自身的碰撞

### 2. 客户端 `bHit` 标记位滞后

原代码 `AuraProjectile.cpp:86-89`：
```cpp
else  // 客户端分支
{
    bHit = true;  // 在 VFX/SFX 播放之后才设 true
}
```

- VFX/SFX 在 `bHit = true` 之前执行，且入口未检查 `bHit`
- 目标角色同时有 `CapsuleComponent` 和 `SkeletalMeshComponent`，均产生 Overlap 事件
- 同一帧内两次 Overlap 都通过了入口，导致 VFX/SFX 播放两遍

## 修复方案

### 1. 自伤检查改用 `AActor::Instigator`

`Instigator` 是引擎内置的 `AActor` 可复制属性，双端可用，效果等价：

```cpp
// 修复前（客户端无效）
if (DamageEffectSpecHandle.Data.Get())
{
    if (DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor)
        return;
}

// 修复后（双端有效）
if (OtherActor == GetInstigator() || bHit)
    return;
```

### 2. `bHit` 提前置位

将 `bHit = true` 从末尾 `else` 分支提升到函数入口，VFX/SFX 之前：

```cpp
if (OtherActor == GetInstigator() || bHit)
    return;

bHit = true;  // 第一时间标记

// 之后才播放 VFX/SFX ...
```

这样同帧第二次 Overlap 在入口就被 `bHit` 拦截，不会重复播放特效。

## 改动文件

- `Source/GameAbilitySystem/Private/Actors/AuraProjectile.cpp`
