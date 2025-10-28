#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GenericFSMComponentBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnumStateChanged, uint8, NewStateValue);

/**
 * 通用有限状态机基类（非模板）
 * 可以挂在 Actor 上，支持蓝图事件
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ADVANCEDFARMINGSYSTEM_API UGenericFSMComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UGenericFSMComponentBase();

	/** 当前状态值（存储枚举的 uint8） */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="FSM")
	uint8 CurrentState;

	/** 蓝图可绑定事件：状态切换时触发 */
	UPROPERTY(BlueprintAssignable, Category="FSM")
	FOnEnumStateChanged OnStateChanged;

	/** Tick 状态机 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** 切换状态 */
	void SetState(uint8 NewState);

protected:
	/** 状态回调表，由派生类注册具体枚举状态逻辑 */
	TMap<uint8, TFunction<TOptional<uint8>(float DeltaTime)>> StateCallbacks;
};
