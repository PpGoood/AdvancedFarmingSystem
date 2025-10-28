// Fill out your copyright notice in the Description page of Project Settings.

#include "Plant/FSM/GenericFSMComponentBase.h"


UGenericFSMComponentBase::UGenericFSMComponentBase()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentState = 0;
}

void UGenericFSMComponentBase::SetState(uint8 NewState)
{
	if (CurrentState == NewState) return;

	CurrentState = NewState;
	OnStateChanged.Broadcast(CurrentState);
}

void UGenericFSMComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (StateCallbacks.Contains(CurrentState))
	{
		TOptional<uint8> NextState = StateCallbacks[CurrentState](DeltaTime);
		if (NextState.IsSet())
		{
			SetState(NextState.GetValue());
		}
	}
}

