// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FVR_SaveComponentData.generated.h"

USTRUCT(BlueprintType)
struct FVR_SaveComponentData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<uint8> byteData;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UClass* ComponentClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FString> StatlineAttributeData;
};