// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

#include "MyActor.h"
#include "Engine/World.h"
#include "Plant/FSM/PlantFSMComponent.h"

// Sets default values
AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// ✅ 创建并附加状态机组件
	PlantFSMComponent = CreateDefaultSubobject<UPlantFSMComponent>(TEXT("PlantFSM"));
	AddInstanceComponent(PlantFSMComponent); // 确保在编辑器中可见（可选）

	// 可选：也可以在这里设置初始状态或参数
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("测试 Actor 启动了！"));
	if (PlantFSMComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("状态机组件已初始化！当前状态：Healthy"));
	}
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ✅ 状态机会在内部自动执行 Tick 逻辑
	// 这里无需手动调用
}

