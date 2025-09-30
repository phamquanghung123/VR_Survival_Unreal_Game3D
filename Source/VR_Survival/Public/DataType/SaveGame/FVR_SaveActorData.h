// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataType/SaveGame/FVR_SaveComponentData.h"
#include "FVR_SaveActorData.generated.h"

USTRUCT(BlueprintType)
struct FVR_SaveActorData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite)
	FTransform ActorTransform;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite)
	TArray<uint8> byteData;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite)
	TArray<FVR_SaveComponentData> ComponentData;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite)
	bool WasSpawned = false;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite)
	UClass* ActorClass = nullptr;

	UPROPERTY(VisibleAnywhere, SaveGame, BlueprintReadWrite)
	TArray<FString> TimerData;


	FVR_SaveActorData()
	{

	}

	FVR_SaveActorData(const FTransform& actorTrans, const bool& wasSpawned, UClass* actorClass)
	{
		ActorTransform = actorTrans;
		WasSpawned = wasSpawned;
		ActorClass = actorClass;
	}

	FVR_SaveActorData(const FTransform& actorTrans, const bool& wasSpawned, UClass* actorClass, TArray<FString> DataTime)
	{
		ActorTransform = actorTrans;
		WasSpawned = wasSpawned;
		ActorClass = actorClass;
		TimerData = DataTime;
	}

};