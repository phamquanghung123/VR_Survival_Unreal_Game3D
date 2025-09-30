// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/VR_SaveGame.h"

void UVR_SaveGame::SetSaveActorData(TMap<FGuid, FVR_SaveActorData> Data)
{
	SaveableActorData = Data;
}

TMap<FGuid, FVR_SaveActorData> UVR_SaveGame::GetSaveActorData()
{
	return SaveableActorData;
}

void UVR_SaveGame::SetCurrentLevel(FName LevelName)
{
	CurrentlyLoadedLevel = LevelName;
}

FName UVR_SaveGame::GetCurrentLevel() const
{
	return CurrentlyLoadedLevel;
}

void UVR_SaveGame::SetPlayerData(FVR_SaveActorData Data)
{
	PlayerData = Data;
}

FVR_SaveActorData UVR_SaveGame::GetPlayerData()
{
	return PlayerData;
}