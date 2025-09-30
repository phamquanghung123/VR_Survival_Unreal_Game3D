// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStruct.generated.h"


UENUM()
enum class EItemQuality : uint8
{
	Shoddy UMETA(DisplayName = "Shoddy"), //kém ch?t lý?ng
	Common UMETA(DisplayName = "Common"), //T?m chung
	Quality UMETA(DisplayName = "Quality"),//ch?t lý?ng good
	Masterwork UMETA(DisplayName = "Masterwork"),//ki?t tác
	Grandmaster UMETA(DisplayName = "Grandmaster"),//;Ð?i ki?n tý?ng
};


USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()
};