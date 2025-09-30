// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType, meta = (ScriptName = "CoreStatEnum"))
enum class EVR_CoreStat : uint8
{
	CS_Health	UMETA(DisplayName = "Health"),
	CS_Stamina	UMETA(DisplayName = "Stamina"),
	CS_Hunger	UMETA(DisplayName = "Hunger"),
	CS_Thirst	UMETA(DisplayName = "Thirst"),
	CS_Blood	UMETA(DisplayName = "Blodd"),
	CS_Calories	UMETA(DisplayName = "Calories"),
	CS_Protien	UMETA(DisplayName = "Protien"),
	CS_Fats		UMETA(DisplayName = "Fats"),
	CS_Carbs	UMETA(DisplayName = "Carbs"),
	CS_Vitamin	UMETA(DisplayName = "Vitamin"),
};

