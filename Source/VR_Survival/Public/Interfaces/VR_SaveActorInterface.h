// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataType/SaveGame/FVR_SaveActorData.h"
#include "VR_SaveActorInterface.generated.h"

UINTERFACE(MinimalAPI)
class UVR_SaveActorInterface : public UInterface
{
	GENERATED_BODY()
};


class VR_SURVIVAL_API IVR_SaveActorInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	FGuid GetActorSaveID();
	virtual FGuid GetActorSaveID_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void SetActorGUID(const FGuid& NewGuid);
	virtual void SetActorGUID_Implementation(const FGuid& NewGuid);

	UFUNCTION(BlueprintNativeEvent)
	void UpdateFromSave();
	virtual void UpdateFromSave_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	FVR_SaveActorData GetSaveData();
	virtual FVR_SaveActorData GetSaveData_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	FVR_SaveComponentData GetComponetSaveData();
	virtual FVR_SaveComponentData GetComponetSaveData_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void SetComponentSaveData(FVR_SaveComponentData Data);
	virtual void SetComponentSaveData_Implementation(FVR_SaveComponentData Data);

	UFUNCTION(BlueprintNativeEvent)
	void SetActorTimerSaveData(const TArray<FString>& RawData);
	virtual void SetActorTimerSaveData_Implementation(const TArray<FString>& RawData);


};
