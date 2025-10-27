// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantBase.generated.h"

//TODO 使用状态机改写植物状态
UCLASS()
class ADVANCEDFARMINGSYSTEM_API APlantBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlantBase();

	void InitializPlant();
	
	//添加可活动喷头
	UFUNCTION(BlueprintCallable)
	void AddActiveSprinkler(AActor* Sprinkler);

	//添加可活动喷头
	UFUNCTION(BlueprintCallable)
	void RemoveActiveSprinkler(AActor* Sprinkler);

	//Grow
	UFUNCTION(BlueprintCallable)
	void InitiliazeGrowingTimer();
	UFUNCTION(BlueprintCallable)
	void PauseGrowth();
	UFUNCTION(BlueprintCallable)
	void UnPauseGrowth();
	UFUNCTION(BlueprintCallable)
	void OnGrow();

	//Decay
	UFUNCTION(BlueprintCallable)
	void InitializeDecayTimer();
	UFUNCTION(BlueprintCallable)
	void PauseDecay();
	UFUNCTION(BlueprintCallable)
	void UnPauseDecay();
	UFUNCTION(BlueprintCallable)
	void OnDecay();

	//Damage
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void TryHarvest(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void TryAddWater(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void TryAddFertilizer(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void TryCurePlant(APlayerController* PlayerController);
	
	UFUNCTION(BlueprintCallable)
	void OnSickness(bool IsSick);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
