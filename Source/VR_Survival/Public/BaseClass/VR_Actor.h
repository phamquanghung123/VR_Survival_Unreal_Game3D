// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/VR_SaveActorInterface.h"
#include "VR_Actor.generated.h"

UCLASS()
class VR_SURVIVAL_API AVR_Actor : public AActor, public IVR_SaveActorInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Components", meta = (AllowPrivateAccess = "true"))
	FGuid SaveID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Components", meta = (AllowPrivateAccess = "true"))
	bool bWasSpawned = false;


public:	

	virtual void BeginPlay() override;
	virtual FGuid GetActorSaveID_Implementation() override;
	virtual void SetActorGUID_Implementation(const FGuid& NewGuid) override;
	virtual FVR_SaveActorData GetSaveData_Implementation() override;
	virtual void UpdateFromSave_Implementation() override;
	void SetWasSpawned(const bool& IsSpawned);


	AVR_Actor();
	virtual void Tick(float DeltaTime) override;

};
