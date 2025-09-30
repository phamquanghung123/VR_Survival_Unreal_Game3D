// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/VR_SaveActorInterface.h"

// Add default functionality here for any IVR_SaveActorInterface functions that are not pure virtual.

FGuid IVR_SaveActorInterface::GetActorSaveID_Implementation()
{
	return FGuid();
}

void IVR_SaveActorInterface::SetActorGUID_Implementation(const FGuid& NewGuid)
{
}

void IVR_SaveActorInterface::UpdateFromSave_Implementation()
{
}

FVR_SaveActorData IVR_SaveActorInterface::GetSaveData_Implementation()
{
	return FVR_SaveActorData();
}

FVR_SaveComponentData IVR_SaveActorInterface::GetComponetSaveData_Implementation()
{
	return FVR_SaveComponentData();
}

void IVR_SaveActorInterface::SetComponentSaveData_Implementation(FVR_SaveComponentData Data)
{
}

void IVR_SaveActorInterface::SetActorTimerSaveData_Implementation(const TArray<FString>& RawData)
{
}
