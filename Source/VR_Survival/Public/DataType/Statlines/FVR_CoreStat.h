// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FVR_CoreStat.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FVR_CoreStat
{
	GENERATED_BODY()

private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Core Stats", meta = (AllowPrivateAccess = "true"))
	float Current = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Core Stats", meta = (AllowPrivateAccess = "true"))
	float Max = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, Category = "Core Stats", meta = (AllowPrivateAccess = "true"))
	double PerSecondTick = 1.0f;

public:

	FVR_CoreStat()
	{

	}

	FVR_CoreStat(const float& current, const float& max, const float& perSecondTick)
	{
		Current = current;
		Max = max;
		PerSecondTick = perSecondTick;
	}


	void TickStat(const float& DeltaTime)
	{
		Current = FMath::Clamp(Current + (PerSecondTick * DeltaTime), 0.0f, Max);
	}

	void Addjust(const float& Amount)
	{
		Current = FMath::Clamp(Current + Amount, 0.0f, Max);
	}

	void ForceAdjust(const float& Amount)
	{
		Current += Amount;
	}

	float Percentile() const
	{
		return FMath::Clamp(Current / Max, 0.0, 1.0);
	}

	void AddjustTick(const float& NewTick)
	{
		PerSecondTick = NewTick;
	}

	float GetCurrent() const
	{
		return Current;
	}

	FString GetSaveString()
	{
		FString Ret = FString::SanitizeFloat(Current);
		Ret += "|";
		Ret += FString::SanitizeFloat(Max);
		Ret += "|";
		Ret += FString::SanitizeFloat(PerSecondTick);
		return Ret;
	}

	void UpdateFromSaveString(TArray<FString> Parts)
	{
		if (Parts.Num() != 3)
		{
			return;
		}
		Current = FCString::Atof(*Parts[0]);
		Max = FCString::Atof(*Parts[1]);
		PerSecondTick = FCString::Atof(*Parts[2]);
	}


};