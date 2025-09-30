// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DataType/SaveGame/FVR_SaveActorData.h"
#include "VR_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class VR_SURVIVAL_API UVR_GameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TMap<FGuid, FVR_SaveActorData> SaveableActorData;
	UPROPERTY()
	class UVR_SaveGame* SaveGameObject = nullptr;
	UPROPERTY()
	FString SaveSlotName = TEXT("DEFAULT");
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName CurrentlyLoadedLevel = "NONE";
	UPROPERTY()
	FVR_SaveActorData PlayerData;
	
	UVR_GameInstance();

	void CreateSaveSlot();
	void GatherActorData();
	void LoadGame();
	void GatherPlayerData();
	void SetPlayerData();

public:

	UFUNCTION(BlueprintCallable)
	void DEV_SaveGame();

	UFUNCTION(BlueprintCallable)
	void DEV_LoadGame();
	
};
