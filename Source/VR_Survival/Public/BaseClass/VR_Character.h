// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/VR_SaveActorInterface.h"
#include "VR_Character.generated.h"

UCLASS()
class VR_SURVIVAL_API AVR_Character : public ACharacter, public IVR_SaveActorInterface
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UVR_StatlineComponent* StatlineComponent;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Components", meta = (AllowPrivateAccess = "true"))
	FGuid ActorSaveID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Components", meta = (AllowPrivateAccess = "true"))
	bool bWasSpawned = false;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void StartJumping();
	UFUNCTION()
	void StopJumped();
	UFUNCTION()
	void StartSprinting();
	UFUNCTION()
	void StopSprinted();

	

public:	

	virtual FGuid GetActorSaveID_Implementation() override;
	virtual FVR_SaveActorData GetSaveData_Implementation() override;
	virtual void SetActorGUID_Implementation(const FGuid& NewGuid) override;
	void SetWasSpawned(const bool& IsSpawned);

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	AVR_Character();


};
