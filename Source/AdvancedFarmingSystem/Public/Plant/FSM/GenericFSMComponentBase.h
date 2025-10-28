#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GenericFSMComponentBase.generated.h"

/** 状态变化委托 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnumStateChanged, uint8, OldStateValue, uint8, NewStateValue);

/** 状态结构体，包含进入/更新/离开回调 */
struct FStateCallbacks
{
	TFunction<void()> OnEnter;
	TFunction<void()> OnExit;
	TFunction<TOptional<uint8>(float DeltaTime)> OnTick;
};

/**
 * 通用FSM组件基类
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ADVANCEDFARMINGSYSTEM_API UGenericFSMComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UGenericFSMComponentBase();

	/** 当前状态 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FSM")
	uint8 CurrentState;

	/** 当前状态持续时间（秒） */ // 新增
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FSM")
	float StateElapsedTime;

	/** 状态变化事件 */
	UPROPERTY(BlueprintAssignable, Category="FSM")
	FOnEnumStateChanged OnStateChanged;

	/** 切换状态 */
	void SetState(uint8 NewState);

	/** 注册状态 */
	void RegisterState(uint8 StateValue, const FStateCallbacks& Callbacks);

	/** 获取当前状态持续时间 */ // 新增
	UFUNCTION(BlueprintCallable, Category="FSM")
	float GetStateElapsedTime() const { return StateElapsedTime; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/** 状态表 */
	TMap<uint8, FStateCallbacks> StateMap;

	/** 是否第一次进入状态 */
	bool bJustEntered = true;
};
