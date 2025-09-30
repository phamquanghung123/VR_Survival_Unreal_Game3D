// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DataType/SaveGame/FVR_SaveActorData.h"

#include "VR_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class VR_SURVIVAL_API UVR_SaveGame : public USaveGame
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TMap < FGuid, struct FVR_SaveActorData> SaveableActorData;
	UPROPERTY()
	FName CurrentlyLoadedLevel = "NONE";
	UPROPERTY()
	FVR_SaveActorData PlayerData;


public:
	void SetSaveActorData(TMap < FGuid, FVR_SaveActorData> Data);
	TMap < FGuid, FVR_SaveActorData> GetSaveActorData();

	void SetCurrentLevel(FName LevelName);
	FName GetCurrentLevel() const;

	void SetPlayerData(FVR_SaveActorData Data);
	FVR_SaveActorData GetPlayerData();



};
