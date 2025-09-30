// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/VR_Character.h"
#include "Components/VR_StatlineComponent.h"


// Sets default values
AVR_Character::AVR_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	StatlineComponent = CreateDefaultSubobject<UVR_StatlineComponent>(TEXT("StatlineComponet"));
	StatlineComponent->SetOwningCurrentMovementComp(GetCharacterMovement());

	ActorSaveID = FGuid::NewGuid();
}

// Called when the game starts or when spawned
void AVR_Character::BeginPlay()
{
	Super::BeginPlay();
	if (!ActorSaveID.IsValid())
	{
		ActorSaveID = FGuid::NewGuid(); // Ensure the GUID is valid
	}
	
}

// Called every frame
void AVR_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVR_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVR_Character::StartJumping()
{
	if (StatlineComponent->CanJumping())
	{
		StatlineComponent->HasJump();
		ACharacter::Jump();
	}
}

void AVR_Character::StopJumped()
{
	ACharacter::StopJumping();
}

void AVR_Character::StartSprinting()
{
	StatlineComponent->SetSprinting(true);
}

void AVR_Character::StopSprinted()
{
	StatlineComponent->SetSprinting(false);
}

FGuid AVR_Character::GetActorSaveID_Implementation()
{
	return ActorSaveID;
}

FVR_SaveActorData AVR_Character::GetSaveData_Implementation()
{
	return FVR_SaveActorData(this->GetActorTransform(), this->bWasSpawned, this->GetClass());
}

void AVR_Character::SetActorGUID_Implementation(const FGuid& NewGuid)
{
	if (ActorSaveID.IsValid())
	{
		ActorSaveID.Invalidate();
	}
	ActorSaveID = NewGuid;
}

void AVR_Character::SetWasSpawned(const bool& IsSpawned)
{
	bWasSpawned = IsSpawned;
}
