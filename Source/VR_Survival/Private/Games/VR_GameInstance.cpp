// Fill out your copyright notice in the Description page of Project Settings.


#include "Games/VR_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Games/VR_SaveGame.h"
#include "BaseClass/VR_Character.h"
#include "GameFramework/Character.h"
#include <EngineUtils.h>
#include "Interfaces/VR_SaveActorInterface.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "VR_Survival/Debug/DebugHelper.h" 
#include "BaseClass/VR_Actor.h"



UVR_GameInstance::UVR_GameInstance()
{

}

void UVR_GameInstance::CreateSaveSlot()
{
	SaveGameObject = Cast<UVR_SaveGame>(UGameplayStatics::CreateSaveGameObject(UVR_SaveGame::StaticClass()));
}

void UVR_GameInstance::GatherActorData()
{
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (!IsValid(Actor) || !Actor->Implements<UVR_SaveActorInterface>())
		{
			continue;
		}

		IVR_SaveActorInterface* Inter = Cast<IVR_SaveActorInterface>(Actor);
		if (Inter == nullptr)
		{
			continue;
		}
		FGuid SAI = Inter->GetActorSaveID_Implementation();
		if (!SAI.IsValid())
		{
			continue;
		}
		FVR_SaveActorData SAD = Inter->GetSaveData_Implementation();

		FMemoryWriter MemWriter(SAD.byteData);
		FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
		Ar.ArIsSaveGame = true;
		Actor->Serialize(Ar);

		for (auto ActorComp : Actor->GetComponents())
		{
			if (!ActorComp->Implements<UVR_SaveActorInterface>())
			{
				continue;
			}
			IVR_SaveActorInterface* CompInter = Cast<IVR_SaveActorInterface>(ActorComp);
			if (CompInter == nullptr)
			{
				continue;
			}
			FVR_SaveComponentData SCD = CompInter->GetComponetSaveData_Implementation();

			FMemoryWriter CompMemWriter(SCD.byteData);
			FObjectAndNameAsStringProxyArchive CAr(CompMemWriter, true);
			CAr.ArIsSaveGame = true;
			ActorComp->Serialize(CAr);
			SCD.ComponentClass = ActorComp->GetClass();

			SAD.ComponentData.Add(SCD);
		}
		SaveableActorData.Add(SAI, SAD);
	}
	GatherPlayerData();
}

void UVR_GameInstance::GatherPlayerData()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	IVR_SaveActorInterface* Inter = Cast<IVR_SaveActorInterface>(PlayerCharacter);
	if (Inter == nullptr) return;

	FVR_SaveActorData SAD = Inter->GetSaveData_Implementation();

	FMemoryWriter MemWriter(SAD.byteData);
	FObjectAndNameAsStringProxyArchive Ar(MemWriter, true);
	Ar.ArIsSaveGame = true;
	PlayerCharacter->Serialize(Ar);
	for (auto ActorComp : PlayerCharacter->GetComponents())
	{
		if (!ActorComp->Implements<UVR_SaveActorInterface>())
		{
			continue;
		}
		IVR_SaveActorInterface* CompInter = Cast<IVR_SaveActorInterface>(ActorComp);
		if (CompInter == nullptr)
		{
			continue;
		}
		FVR_SaveComponentData SCD = CompInter->GetComponetSaveData_Implementation();

		FMemoryWriter CompMemWriter(SCD.byteData);
		FObjectAndNameAsStringProxyArchive CAr(CompMemWriter, true);
		CAr.ArIsSaveGame = true;
		ActorComp->Serialize(CAr);
		SCD.ComponentClass = ActorComp->GetClass();
		SAD.ComponentData.Add(SCD);
	}
	PlayerData = SAD;
}

void UVR_GameInstance::LoadGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		Debug::Print(TEXT("SaveSlotName"), FColor::Red);
		return;
	}

	SaveableActorData.Empty();
	SaveGameObject = Cast<UVR_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	SaveableActorData = SaveGameObject->GetSaveActorData();
	PlayerData = SaveGameObject->GetPlayerData();
	CurrentlyLoadedLevel = SaveGameObject->GetCurrentLevel();

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (!IsValid(Actor) || Actor->Implements<UVR_SaveActorInterface>())
		{
			continue;
		}
		IVR_SaveActorInterface* Inter = Cast<IVR_SaveActorInterface>(Actor);
		if (Inter == nullptr)
		{
			continue;
		}
		if (Inter->Execute_GetSaveData(Actor).WasSpawned)
		{
			Actor->Destroy();
		}
	}

	for (TTuple<FGuid, FVR_SaveActorData> SAD : SaveableActorData)
	{
		if (SAD.Value.WasSpawned)
		{
			UClass* ToSpawnClass = SAD.Value.ActorClass;
			if (ToSpawnClass->IsChildOf(AVR_Character::StaticClass()))
			{
				AVR_Character* CSpawned = GetWorld()->SpawnActor<AVR_Character>(ToSpawnClass, SAD.Value.ActorTransform);
				IVR_SaveActorInterface* CInter = Cast<IVR_SaveActorInterface>(CSpawned);
				if (CInter == nullptr)
				{
					CSpawned->Destroy();
					continue;
				}
				CInter->Execute_SetActorGUID(CSpawned, SAD.Key);
				CSpawned->SetWasSpawned(true);
				continue;
			}
			AVR_Actor* ASpawned = GetWorld()->SpawnActor<AVR_Actor>(ToSpawnClass, SAD.Value.ActorTransform);
			IVR_SaveActorInterface* AInter = Cast<IVR_SaveActorInterface>(ASpawned);
			if (ASpawned == nullptr)
			{
				ASpawned->Destroy();
				continue;
			}
			AInter->Execute_SetActorGUID(ASpawned, SAD.Key);
			ASpawned->SetWasSpawned(true);
		}

	}

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (!IsValid(Actor) || !Actor->Implements<UVR_SaveActorInterface>())
		{
			continue;
		}
		IVR_SaveActorInterface* Inter = Cast<IVR_SaveActorInterface>(Actor);
		if (Inter == nullptr)
		{
			continue;
		}
		FGuid SAI = Inter->GetActorSaveID_Implementation();
		if (!SaveableActorData.Find(SAI))
		{
			continue;
		}
		FVR_SaveActorData SAD = SaveableActorData[SAI];
		Actor->SetActorTransform(SAD.ActorTransform);

		FMemoryReader MemReader(SAD.byteData);
		FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
		Ar.ArIsSaveGame = true;
		Actor->Serialize(Ar);
		Inter->Execute_UpdateFromSave(Actor);
		Inter->Execute_SetActorTimerSaveData(Actor, SAD.TimerData);

		for (auto ActorComp : Actor->GetComponents())
		{
			if (!IsValid(ActorComp) || !ActorComp->Implements<UVR_SaveActorInterface>())
			{
				continue;
			}
			IVR_SaveActorInterface* InterComp = Cast<IVR_SaveActorInterface>(ActorComp);
			if (InterComp == nullptr)
			{
				continue;
			}
			for (auto SCD : SAD.ComponentData)
			{
				if (SCD.ComponentClass != ActorComp->GetClass())
				{
					continue;
				}
				FMemoryReader CompoMemReader(SCD.byteData);
				FObjectAndNameAsStringProxyArchive CAr(CompoMemReader, true);
				CAr.ArIsSaveGame = true;
				ActorComp->Serialize(CAr);
				if (SCD.StatlineAttributeData.IsEmpty())
				{
					break;
				}
				InterComp->Execute_SetComponentSaveData(ActorComp, SCD);
				break;
			}
		}
	}
	SetPlayerData();
}

void UVR_GameInstance::SetPlayerData()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	IVR_SaveActorInterface* Inter = Cast<IVR_SaveActorInterface>(PlayerCharacter);
	if (Inter == nullptr)
	{
		Debug::Print(TEXT("Inter PlayerCharacter"), FColor::Red);
		return;
	}

	PlayerCharacter->SetActorTransform(PlayerData.ActorTransform);
	FMemoryReader MemReader(PlayerData.byteData);
	FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
	Ar.ArIsSaveGame = true;
	PlayerCharacter->Serialize(Ar);

	for (auto ActorComp : PlayerCharacter->GetComponents())
	{
		if (!IsValid(ActorComp) || !ActorComp->Implements<UVR_SaveActorInterface>())
		{
			continue;
		}
		IVR_SaveActorInterface* InterComp = Cast<IVR_SaveActorInterface>(ActorComp);
		if (InterComp == nullptr)
		{
			continue;
		}
		for (auto SCD : PlayerData.ComponentData)
		{
			if (SCD.ComponentClass != ActorComp->GetClass())
			{
				continue;
			}
			FMemoryReader CompoMemReader(SCD.byteData);
			FObjectAndNameAsStringProxyArchive CAr(CompoMemReader, true);
			CAr.ArIsSaveGame = true;
			ActorComp->Serialize(CAr);
			if (SCD.StatlineAttributeData.IsEmpty())
			{
				break;
			}
			InterComp->SetComponentSaveData_Implementation(SCD);
			break;
		}
	}
	Inter->Execute_UpdateFromSave(PlayerCharacter);
}



void UVR_GameInstance::DEV_SaveGame()
{
	if (SaveGameObject == nullptr)
	{
		CreateSaveSlot();
	}
	GatherActorData();
	SaveGameObject->SetSaveActorData(SaveableActorData);
	SaveGameObject->SetPlayerData(PlayerData);
	SaveGameObject->SetCurrentLevel(CurrentlyLoadedLevel);
	UGameplayStatics::SaveGameToSlot(SaveGameObject, SaveSlotName, 0);
}

void UVR_GameInstance::DEV_LoadGame()
{
	LoadGame();
}
