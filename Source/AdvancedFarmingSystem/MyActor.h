// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"


class UPlantFSMComponent;

UCLASS()
class ADVANCEDFARMINGSYSTEM_API AMyActor : public AActor
{
	GENERATED_BODY()
public:	
	AMyActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FSM", meta = (AllowPrivateAccess = "true"))
	UPlantFSMComponent* PlantFSMComponent;  // ✅ FSM 组件引用
};
