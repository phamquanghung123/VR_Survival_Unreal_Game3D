// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/VR_Actor.h"

// Sets default values
AVR_Actor::AVR_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SaveID = FGuid::NewGuid();
}

// Called when the game starts or when spawned
void AVR_Actor::BeginPlay()
{
	Super::BeginPlay();
	if (!SaveID.IsValid())
	{
		SaveID = FGuid::NewGuid(); // Ensure the GUID is valid
	}
	
}

FGuid AVR_Actor::GetActorSaveID_Implementation()
{
	return SaveID;
}

void AVR_Actor::SetActorGUID_Implementation(const FGuid& NewGuid)
{
	if (SaveID.IsValid())
	{
		SaveID.Invalidate(); // Invalidate the old GUID if it was valid
	}
	SaveID = NewGuid;
}
void AVR_Actor::SetWasSpawned(const bool& IsSpawned)
{
	bWasSpawned = IsSpawned;
}

FVR_SaveActorData AVR_Actor::GetSaveData_Implementation()
{
	return FVR_SaveActorData(this->GetActorTransform(), this->bWasSpawned, this->GetClass());
}

void AVR_Actor::UpdateFromSave_Implementation()
{

}

// Called every frame
void AVR_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

