#pragma once

#include "CoreMinimal.h"
#include "GenericFSMComponentBase.h"
#include "PlantFSMComponent.generated.h"

/**
 * 植物状态枚举
 */
UENUM(BlueprintType)
enum class EPlantState : uint8
{
	Healthy       UMETA(DisplayName = "健康"),
	Sick          UMETA(DisplayName = "生病"),
	Wilted        UMETA(DisplayName = "枯萎"),
	Harvestable   UMETA(DisplayName = "可收获"),
};

/**
 * 植物状态机组件
 * 挂在植物Actor上即可使用
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ADVANCEDFARMINGSYSTEM_API UPlantFSMComponent : public UGenericFSMComponentBase
{
	GENERATED_BODY()

public:
	UPlantFSMComponent();
};
