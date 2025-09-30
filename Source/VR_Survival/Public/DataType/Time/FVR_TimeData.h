// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VR_Survival/Debug/DebugHelper.h"
#include "FVR_TimeData.generated.h"


USTRUCT(BlueprintType)
struct FVR_TimeData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, Category = "Time Data")
	int DayOfYear = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, Category = "Time Data")
	int Year = 2025;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, Category = "Time Data")
	int Month = 12;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, Category = "Time Data")
	int Day = 30;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, Category = "Time Data")
	int Hour = 9;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, SaveGame, Category = "Time Data")
	int Minute = 23;


	FString GetSaveString()
	{
		FString Ret = FString::FromInt(DayOfYear);
		Ret += "|";
		Ret += FString::FromInt(Year);
		Ret += "|";
		Ret += FString::FromInt(Month);
		Ret += "|";
		Ret += FString::FromInt(Day);
		Ret += "|";
		Ret += FString::FromInt(Hour);
		Ret += "|";
		Ret += FString::FromInt(Minute);
		return Ret;
	}

	void UpdateFromSaveString(TArray<FString> Parts)
	{
		if (Parts.Num() != 6)
		{
			Debug::Print(TEXT("FTimeData::UpdateFromSaveString called with other then 6 parts"), FColor::Red);
			return;
		}
		DayOfYear = FCString::Atof(*Parts[0]);
		Year = FCString::Atof(*Parts[1]);
		Month = FCString::Atof(*Parts[2]);
		Day = FCString::Atof(*Parts[3]);
		Hour = FCString::Atof(*Parts[4]);
		Minute = FCString::Atof(*Parts[5]);
	};
};