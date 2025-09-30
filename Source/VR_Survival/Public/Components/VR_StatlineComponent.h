// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataType/Statlines/FVR_CoreStat.h"
#include "Interfaces/VR_SaveActorInterface.h"
#include "VR_StatlineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR_SURVIVAL_API UVR_StatlineComponent : public UActorComponent, public IVR_SaveActorInterface
{
	GENERATED_BODY()


private:

	class UCharacterMovementComponent* OwningCurrentMovementComp;

	UPROPERTY(EditAnywhere, Category = "Statline", SaveGame, meta = (AllowPrivateAccess = "true"))
	FVR_CoreStat Health;

	UPROPERTY(EditAnywhere, Category = "Statline", SaveGame, meta = (AllowPrivateAccess = "true"))
	FVR_CoreStat Stamina;

	UPROPERTY(EditAnywhere, Category = "Statline", SaveGame, meta = (AllowPrivateAccess = "true"))
	FVR_CoreStat Hunger = FVR_CoreStat(100, 100, -5);

	UPROPERTY(EditAnywhere, Category = "Statline", SaveGame, meta = (AllowPrivateAccess = "true"))
	FVR_CoreStat Thirst = FVR_CoreStat(100, 100, -5);

	UPROPERTY(EditAnywhere, Category = "Statline", meta = (AllowPrivateAccess = "true"))
	float ThirstyDamageHealth = 1.f;

	UPROPERTY(EditAnywhere, Category = "Statline", meta = (AllowPrivateAccess = "true"))
	float HungryDamageHealth = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Statline", meta = (AllowPrivateAccess = "true"))
	float SecondForStaminaExhaustion = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Statline")
	float ExHaustionStaminaCooldown = 0.f;


	void TickStat(float DeltaTime);
	void TickHealth(float DeltaTime);
	void TickStamina(float DeltaTime);
	void TickHunger(float DeltaTime);
	void TickThirst(float DeltaTime);

	bool CanHealHealth() const;


	UPROPERTY(EditAnywhere, Category = "Statline")
	float JumpCost = 10.f;

	UPROPERTY(EditAnywhere, Category = "Statline")
	float SprintingCost = 1.f;

	UPROPERTY(EditAnywhere, Category = "Statline")
	float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Statline")
	float SprintSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Statline")
	bool bIsSprinting = false;

public:
	void SetSprinting(const bool bSprinting);
	bool IsValidSprinting();

	void HasJump();
	bool CanJumping() const;


	

protected:
	virtual void BeginPlay() override;
	UVR_StatlineComponent();

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual FVR_SaveComponentData GetComponetSaveData_Implementation() override;
	virtual void SetComponentSaveData_Implementation(FVR_SaveComponentData Data) override;

	UFUNCTION(BlueprintCallable)

	float GetPercentileStat(enum EVR_CoreStat Stat) const;

	void SetOwningCurrentMovementComp(UCharacterMovementComponent* OwningMovementComp);


		
};
