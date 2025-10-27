// StateMachine.h
#pragma once
#include "CoreMinimal.h"

template<typename TOwner>
class StateMachine;

/** 状态接口 */
template<typename TOwner>
class IState
{
public:
    virtual ~IState() = default;

    /** 获取状态名 */
    virtual FName GetStateName() const = 0;

    /** 进入状态 */
    virtual void OnEnter() = 0;

    /** 状态更新 */
    virtual void OnUpdate(float DeltaTime) = 0;

    /** 退出状态 */
    virtual void OnExit() = 0;

    TOwner* Owner = nullptr;
    class StateMachine<TOwner>* Machine = nullptr;
};

/** 基础状态类 */
template<typename TOwner, typename TMachine = class StateMachine<TOwner>>
class BaseState : public IState<TOwner>
{
public:
    BaseState(TOwner* InOwner, TMachine* InMachine)
    {
        this->Owner = InOwner;
        this->Machine = InMachine;
    }
};

/** 状态机类 */
template<typename TOwner>
class StateMachine
{
public:
    StateMachine(TOwner* InTarget)
        : Target(InTarget)
    {}

    /** 注册状态 */
    template<typename TState>
    void RegisterState()
    {
        static_assert(std::is_base_of<IState<TOwner>, TState>::value, "TState must inherit from IState<TOwner>");
        TSharedPtr<TState> StateObj = MakeShared<TState>(Target, this);
        StateMap.Add(StateObj->GetStateName(), StaticCastSharedPtr<IState<TOwner>>(StateObj));
    }

    /** 切换状态 */
    void ChangeStateByName(FName Name)
    {
        if (!StateMap.Contains(Name))
        {
            UE_LOG(LogTemp, Warning, TEXT("State [%s] not found."), *Name.ToString());
            return;
        }

        if (CurState.IsValid() && CurState->GetStateName() == Name)
        {
            return;
        }

        NextState = StateMap[Name];
    }

    /** 更新状态机 */
    void Update(float DeltaTime)
    {
        if (NextState.IsValid())
        {
            DoChangeState();
        }

        if (CurState.IsValid())
        {
            CurState->OnUpdate(DeltaTime);
        }
    }

    /** 获取当前状态名 */
    FName GetCurrentStateName() const
    {
        return CurState.IsValid() ? CurState->GetStateName() : NAME_None;
    }

protected:
    void DoChangeState()
    {
        if (CurState.IsValid())
        {
            CurState->OnExit();
            if (OnStateExit)
            {
                OnStateExit(CurState);
            }
        }

        CurState = NextState;
        NextState.Reset();

        if (CurState.IsValid())
        {
            if (OnStateEnter)
            {
                OnStateEnter(CurState);
            }
            CurState->OnEnter();
        }
    }

public:
    /** 状态进入/退出事件回调 */
    TFunction<void(TSharedPtr<IState<TOwner>>)> OnStateEnter;
    TFunction<void(TSharedPtr<IState<TOwner>>)> OnStateExit;

private:
    TOwner* Target = nullptr;
    TMap<FName, TSharedPtr<IState<TOwner>>> StateMap;
    TSharedPtr<IState<TOwner>> CurState;
    TSharedPtr<IState<TOwner>> NextState;
};
