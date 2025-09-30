// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClass/VR_Actor.h"
#include "DataType/Time/FVR_TimeData.h"
#include "VR_ChronomangerBase.generated.h"


class UDirectionalLightComponent;
class USkyLightComponent;
class USkyAtmosphereComponent;
class UExponentialHeightFogComponent;
class UVolumetricCloudComponent;
class UPostProcessComponent;
class UNiagaraComponent;
class UCurveLinearColor;
/**
 * 
 */
UCLASS()
class VR_SURVIVAL_API AVR_ChronomangerBase : public AVR_Actor
{
	GENERATED_BODY()
	
private:
#pragma region WeatherLight

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	UDirectionalLightComponent* SunDirectionalLight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	UDirectionalLightComponent* MoonDirectionalLight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	USkyLightComponent* SkyLight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	UExponentialHeightFogComponent* ExponentialHeightFog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	USkyAtmosphereComponent* SkyAtmosphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	UPostProcessComponent* PostProcess;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	UVolumetricCloudComponent* VolumetricCloud;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	UStaticMeshComponent* SM_SkySphere;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")

	UCurveLinearColor* DailySunAndMoonLightRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")

	UCurveLinearColor* AnnualSunAndMoonLightRotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")

	UCurveLinearColor* MoonLightSettingsBasic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")

	UCurveLinearColor* SunLightSettingsBasic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")

	UCurveLinearColor* SkyAtmosphereSettingsBasic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")

	UCurveLinearColor* MaterialMoonSettingsBasic;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	float Drawn = 360.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	float Dusk = 1080.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	float DEBUG_Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	UMaterialInstanceDynamic* MaterialSkysphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	bool bShouldShowStars = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	bool bShouldShowMoon = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	float MoonScale = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	float MoonRotation = 2.288139f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Lighting")
	float MoonBrightness = 1.f;


	float OffsetDrawnDusk = 0;

	void InitSkySphereMaterial();

	void UpdateDayLight();

	void UpdateNightLight();

	void UpdateRotationSunMoon();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsDay() const;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsNight() const;

	void VisibilitySunOrMoon();

	

#pragma endregion

#pragma region Time

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Time")
	bool bUseDayNightCycle = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Timer")
	FVR_TimeData CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Time")
	float DayLengthInMinutes = 10.0f;

	float TimeDecay = 0.0f;
	float MinuteLenght = 0.0f;
	bool bTimeWasUpdated = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = "true", ToolTip = "Use Day/Night cycle"), Category = "Chrono|Time")
	float CurrentTimeOfDay = 0.0f;

	void UpdateTime(const float& Deltatime);
	void AdvanceMinute();
	void AdvanceHour();
	void AdvanceDay();
	void AdvanceMonth();
	void AdvanceYear();

	void UpdateDayCurrentOfYear();
	void CalculateDayLenght();
	void UpdateTimeOfDayRef();
	void AddDayOfYear();


#pragma endregion
public:

	AVR_ChronomangerBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void UpdateFromSave_Implementation() override;
	virtual FVR_SaveActorData GetSaveData_Implementation() override;
	virtual void SetActorTimerSaveData_Implementation(const TArray<FString>& RawData) override;

};
