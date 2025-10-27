// Fill out your copyright notice in the Description page of Project Settings.


#include "Plant/PlantBase.h"

// Sets default values
APlantBase::APlantBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APlantBase::InitializPlant()
{
}

void APlantBase::AddActiveSprinkler(AActor* Sprinkler)
{
}

void APlantBase::RemoveActiveSprinkler(AActor* Sprinkler)
{
}

void APlantBase::PauseGrowth()
{
}

void APlantBase::UnPauseGrowth()
{
}

void APlantBase::InitiliazeGrowingTimer()
{
}

void APlantBase::OnGrow()
{
}

void APlantBase::InitializeDecayTimer()
{
}

void APlantBase::PauseDecay()
{
}

void APlantBase::UnPauseDecay()
{
}

void APlantBase::OnDecay()
{
}

void APlantBase::TakeDamage(float Damage)
{
}

void APlantBase::TryHarvest(APlayerController* PlayerController)
{
}

void APlantBase::TryAddWater(APlayerController* PlayerController)
{
}

void APlantBase::TryAddFertilizer(APlayerController* PlayerController)
{
}

void APlantBase::TryCurePlant(APlayerController* PlayerController)
{
}

void APlantBase::OnSickness(bool IsSick)
{
}

// Called when the game starts or when spawned
void APlantBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlantBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

