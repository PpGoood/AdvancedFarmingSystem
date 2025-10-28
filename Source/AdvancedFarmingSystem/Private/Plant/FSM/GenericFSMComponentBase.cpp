#include "Plant/FSM/GenericFSMComponentBase.h"

UGenericFSMComponentBase::UGenericFSMComponentBase()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentState = 0;
	StateElapsedTime = 0.f; // 新增
}

void UGenericFSMComponentBase::BeginPlay()
{
	Super::BeginPlay();

	if (StateMap.Contains(CurrentState) && StateMap[CurrentState].OnEnter)
	{
		StateMap[CurrentState].OnEnter();
	}
}

void UGenericFSMComponentBase::SetState(uint8 NewState)
{
	if (CurrentState == NewState)
		return;

	uint8 OldState = CurrentState;

	// 调用离开状态
	if (StateMap.Contains(OldState) && StateMap[OldState].OnExit)
	{
		StateMap[OldState].OnExit();
	}

	CurrentState = NewState;
	bJustEntered = true;
	StateElapsedTime = 0.f; // 新增：切换状态时清零计时器

	// 调用进入状态
	if (StateMap.Contains(NewState) && StateMap[NewState].OnEnter)
	{
		StateMap[NewState].OnEnter();
	}

	OnStateChanged.Broadcast(OldState, NewState);
}

void UGenericFSMComponentBase::RegisterState(uint8 StateValue, const FStateCallbacks& Callbacks)
{
	StateMap.Add(StateValue, Callbacks);
}

void UGenericFSMComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!StateMap.Contains(CurrentState))
		return;

	// 新增：累加状态持续时间
	StateElapsedTime += DeltaTime;

	const FStateCallbacks& Callbacks = StateMap[CurrentState];

	// 调用状态Tick
	if (Callbacks.OnTick)
	{
		TOptional<uint8> Next = Callbacks.OnTick(DeltaTime);
		if (Next.IsSet() && Next.GetValue() != CurrentState)
		{
			SetState(Next.GetValue());
		}
	}

	bJustEntered = false;
}
