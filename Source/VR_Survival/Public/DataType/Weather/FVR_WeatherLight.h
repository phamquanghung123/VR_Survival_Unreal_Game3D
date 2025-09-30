// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataType/Weather/EVR_WeatherType.h"
#include "FVR_WeatherLight.generated.h"

USTRUCT()
struct FDirectionalLightSettings
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, SaveGame, Category = "Directional")
	float DirLightInventory = 7.f;
	UPROPERTY(EditAnywhere, SaveGame, Category = "Directional")
	FLinearColor DirLightColor = FLinearColor::White;
	UPROPERTY(EditAnywhere, SaveGame, Category = "Directional")
	float DirLightSourceAngle = 5.f;
	UPROPERTY(EditAnywhere, SaveGame, Category = "Directional")
	float Temperature = 6500.f;
};

USTRUCT()
struct FSkyLightSetting
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, SaveGame, Category = "SkyLight")
	float SkyLightInventoryScale = 1.f;
};

USTRUCT()
struct FSkyAtmosphereSettings
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, SaveGame, Category = "SkyAtmosphere")
	float Multi = 1.f;

	UPROPERTY(EditAnywhere, SaveGame, Category = "SkyAtmosphere")
	FLinearColor RayleighScattering = FLinearColor(0.176471f, 0.407843f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, SaveGame, Category = "SkyAtmosphere")
	float MieScatteringScale = 0.003996f;

	UPROPERTY(EditAnywhere, SaveGame, Category = "SkyAtmosphere")
	float MieAbsorptionScale = 0.000444f;

	UPROPERTY(EditAnywhere, SaveGame, Category = "SkyAtmosphere")
	float MieAnisotropy = 0.8f;

	UPROPERTY(EditAnywhere, SaveGame, Category = "SkyAtmosphere")
	float AerialPerspectiveViewDistanceScale = 1.f;
};

USTRUCT()
struct FExponentialHeightFogSettings
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, SaveGame, Category = "ExponentialHeightFog")
	FLinearColor EmissiveColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, SaveGame, Category = "ExponentialHeightFog")
	float ExtinctionScale = 0.5f;

};

USTRUCT(BlueprintType)
struct FVR_WeatherLight
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, SaveGame, Category = "WeatherLight")
	EVR_WeatherType WeatherType = EVR_WeatherType::SUNNY;

	UPROPERTY(EditAnywhere, SaveGame, Category = "WeatherLight")
	FDirectionalLightSettings DirectionalLight;

	UPROPERTY(EditAnywhere, SaveGame, Category = "WeatherLight")
	FSkyLightSetting SkyLight;

	UPROPERTY(EditAnywhere, SaveGame, Category = "WeatherLight")
	FSkyAtmosphereSettings SkyAtmosphere;
};