// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VR_StatlineComponent.h"
#include "DataType/Statlines/EVR_CoreStat.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "VR_Utils.h"


UVR_StatlineComponent::UVR_StatlineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UVR_StatlineComponent::SetOwningCurrentMovementComp(UCharacterMovementComponent* OwningMovementComp)
{
	OwningCurrentMovementComp = OwningMovementComp;
}

void UVR_StatlineComponent::TickStat(float DeltaTime)
{
	TickStamina(DeltaTime);
	TickHunger(DeltaTime);
	TickThirst(DeltaTime);
	TickHealth(DeltaTime);
}

void UVR_StatlineComponent::TickHealth(float DeltaTime)
{
	if (!CanHealHealth()) return;
	Health.TickStat(DeltaTime);
}

bool UVR_StatlineComponent::CanHealHealth() const
{
	return !(Hunger.GetCurrent() <= 0.f) || !(Thirst.GetCurrent() <= 0.f);
}



void UVR_StatlineComponent::TickStamina(float DeltaTime)
{
	if (ExHaustionStaminaCooldown > 0)
	{
		ExHaustionStaminaCooldown -= DeltaTime;
		return;
	}
	if (IsValidSprinting())
	{
		Stamina.TickStat(-(DeltaTime * SprintingCost));
		if (Stamina.GetCurrent() <= 0)
		{
			SetSprinting(false);
			ExHaustionStaminaCooldown = SecondForStaminaExhaustion;
		}
		return;
	}
	Stamina.TickStat(DeltaTime);
}

void UVR_StatlineComponent::TickHunger(float DeltaTime)
{
	if (Hunger.GetCurrent() <= 0)
	{
		Health.TickStat(-HungryDamageHealth);
		return;
	}
	Hunger.TickStat(DeltaTime);
}

void UVR_StatlineComponent::TickThirst(float DeltaTime)
{
	if (Thirst.GetCurrent() <= 0)
	{
		Health.TickStat(-ThirstyDamageHealth);
		return;
	}
	Thirst.TickStat(DeltaTime);
}

void UVR_StatlineComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UVR_StatlineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TickType != ELevelTick::LEVELTICK_TimeOnly)
	{
		TickStat(DeltaTime);
	}
}

FVR_SaveComponentData UVR_StatlineComponent::GetComponetSaveData_Implementation()
{
	FVR_SaveComponentData Ref;
	Ref.ComponentClass = this->GetClass();
	Ref.StatlineAttributeData.Add(Health.GetSaveString());
	Ref.StatlineAttributeData.Add(Stamina.GetSaveString());
	Ref.StatlineAttributeData.Add(Hunger.GetSaveString());
	Ref.StatlineAttributeData.Add(Thirst.GetSaveString());

	return Ref;
}

void UVR_StatlineComponent::SetComponentSaveData_Implementation(FVR_SaveComponentData Data)
{
	TArray<FString> Parts;
	for (int i = 0; i < Data.StatlineAttributeData.Num(); i++)
	{
		Parts.Empty();
		Parts = ChopString(Data.StatlineAttributeData[i], '|');
		switch (i)
		{
		case 0:
			Health.UpdateFromSaveString(Parts);
			break;
		case 1:
			Stamina.UpdateFromSaveString(Parts);
			break;
		case 2:
			Hunger.UpdateFromSaveString(Parts);
			break;
		case 3:
			Thirst.UpdateFromSaveString(Parts);
			break;
		default:
			//Log Error
			break;
		}
	}
}

float UVR_StatlineComponent::GetPercentileStat( EVR_CoreStat Stat) const
{
	switch (Stat)
	{
	case EVR_CoreStat::CS_Health:
		return Health.Percentile();
	case EVR_CoreStat::CS_Hunger:
		return Hunger.Percentile();
	case EVR_CoreStat::CS_Stamina:
		return Stamina.Percentile();
	case EVR_CoreStat::CS_Thirst:
		return Thirst.Percentile();
	default:
		return -1;
	}
	
}

void UVR_StatlineComponent::SetSprinting(const bool bSprinting)
{
	bIsSprinting = bSprinting;
	OwningCurrentMovementComp->MaxWalkSpeed = bIsSprinting ? SprintSpeed : WalkSpeed;
}

bool UVR_StatlineComponent::IsValidSprinting()
{
	return bIsSprinting && OwningCurrentMovementComp->MaxWalkSpeed == SprintSpeed && !OwningCurrentMovementComp->IsFalling();
}

void UVR_StatlineComponent::HasJump()
{
	Stamina.Addjust(-JumpCost);
}

bool UVR_StatlineComponent::CanJumping() const
{
	return Stamina.GetCurrent() > JumpCost && !OwningCurrentMovementComp->IsFalling();
}