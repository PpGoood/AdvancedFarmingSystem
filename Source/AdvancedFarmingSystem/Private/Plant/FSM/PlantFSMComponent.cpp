// Fill out your copyright notice in the Description page of Project Settings.

#include "Plant/FSM/PlantFSMComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"

UPlantFSMComponent::UPlantFSMComponent()
{
    auto PrintOnScreen = [](const FString& Msg, const FColor& Color)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, Color, Msg);
        }
    };

    // Healthy 状态
    {
        FStateCallbacks Callbacks;
        Callbacks.OnEnter = [this, PrintOnScreen]() 
        { 
            FString Msg = TEXT("进入 Healthy 状态");
            UE_LOG(LogTemp, Log, TEXT("%s"), *Msg);
            PrintOnScreen(Msg, FColor::Green);
        };
        Callbacks.OnExit  = [this, PrintOnScreen]() 
        { 
            FString Msg = TEXT("离开 Healthy 状态");
            UE_LOG(LogTemp, Log, TEXT("%s"), *Msg);
            PrintOnScreen(Msg, FColor::Yellow);
        };
        Callbacks.OnTick  = [this](float DeltaTime) -> TOptional<uint8>
        {
            if (GetStateElapsedTime() >= 5.f)
                return (uint8)EPlantState::Sick;
            return TOptional<uint8>();
        };
        RegisterState((uint8)EPlantState::Healthy, Callbacks);
    }

    // Sick 状态
    {
        FStateCallbacks Callbacks;
        Callbacks.OnEnter = [this, PrintOnScreen]() 
        { 
            FString Msg = TEXT("进入 Sick 状态");
            UE_LOG(LogTemp, Log, TEXT("%s"), *Msg);
            PrintOnScreen(Msg, FColor::Red);
        };
        Callbacks.OnExit  = [this, PrintOnScreen]() 
        { 
            FString Msg = TEXT("离开 Sick 状态");
            UE_LOG(LogTemp, Log, TEXT("%s"), *Msg);
            PrintOnScreen(Msg, FColor::Orange);
        };
        Callbacks.OnTick  = [this](float DeltaTime) -> TOptional<uint8>
        {
            if (GetStateElapsedTime() >= 5.f)
                return (uint8)EPlantState::Wilted;
            return TOptional<uint8>();
        };
        RegisterState((uint8)EPlantState::Sick, Callbacks);
    }

    // Wilted 状态
    {
        FStateCallbacks Callbacks;
        Callbacks.OnEnter = [this, PrintOnScreen]() 
        { 
            FString Msg = TEXT("进入 Wilted 状态");
            UE_LOG(LogTemp, Log, TEXT("%s"), *Msg);
            PrintOnScreen(Msg, FColor::Purple);
        };
        Callbacks.OnExit  = [this, PrintOnScreen]() 
        { 
            FString Msg = TEXT("离开 Wilted 状态");
            UE_LOG(LogTemp, Log, TEXT("%s"), *Msg);
            PrintOnScreen(Msg, FColor::Silver);
        };
        Callbacks.OnTick  = [this](float DeltaTime) -> TOptional<uint8>
        {
            if (GetStateElapsedTime() >= 5.f)
                return (uint8)EPlantState::Harvestable;
            return TOptional<uint8>();
        };
        RegisterState((uint8)EPlantState::Wilted, Callbacks);
    }

    // Harvestable 状态
    {
        FStateCallbacks Callbacks;
        Callbacks.OnEnter = [this, PrintOnScreen]() 
        { 
            FString Msg = TEXT("进入 Harvestable 状态");
            UE_LOG(LogTemp, Log, TEXT("%s"), *Msg);
            PrintOnScreen(Msg, FColor::Cyan);
        };
        Callbacks.OnExit  = [this, PrintOnScreen]() 
        { 
            FString Msg = TEXT("离开 Harvestable 状态");
            UE_LOG(LogTemp, Log, TEXT("%s"), *Msg);
            PrintOnScreen(Msg, FColor::Magenta);
        };
        Callbacks.OnTick  = [this](float DeltaTime) -> TOptional<uint8>
        {
            if (GetStateElapsedTime() >= 5.f)
                return (uint8)EPlantState::Healthy; // 收获完毕回到健康状态
            return TOptional<uint8>();
        };
        RegisterState((uint8)EPlantState::Harvestable, Callbacks);
    }

    // 设置初始状态
    SetState((uint8)EPlantState::Healthy);
}
