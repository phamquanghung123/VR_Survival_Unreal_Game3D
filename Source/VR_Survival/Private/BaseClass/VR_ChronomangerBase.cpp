// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass/VR_ChronomangerBase.h"
#include "Engine/Light.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "GameFramework/Info.h"
#include "Components/VolumetricCloudComponent.h"
#include "Components/PostProcessComponent.h"
#include "Curves/CurveFloat.h"
#include "Curves/CurveLinearColor.h"
#include "Kismet/GameplayStatics.h"
#include "VR_Survival/Debug/DebugHelper.h" 
#include "VR_Utils.h"




AVR_ChronomangerBase::AVR_ChronomangerBase()
{
    PrimaryActorTick.bCanEverTick = true;

    PostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
    PostProcess->SetupAttachment(RootComponent);

    SunDirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunDirectional"));
    SunDirectionalLight->SetupAttachment(RootComponent);

    MoonDirectionalLight = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("MoonDirectional"));
    MoonDirectionalLight->SetupAttachment(RootComponent);

    SkyLight = CreateDefaultSubobject<USkyLightComponent>(TEXT("SkyLight"));
    SkyLight->SetupAttachment(RootComponent);

    SkyAtmosphere = CreateDefaultSubobject<USkyAtmosphereComponent>(TEXT("SkyAtmosphere"));
    SkyAtmosphere->SetupAttachment(RootComponent);

    ExponentialHeightFog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("ExponenttialHeightFog"));
    ExponentialHeightFog->SetupAttachment(RootComponent);

    VolumetricCloud = CreateDefaultSubobject<UVolumetricCloudComponent>(TEXT("VolumetricCloud"));
    VolumetricCloud->SetupAttachment(RootComponent);

    SM_SkySphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_SkySphere"));
    SM_SkySphere->SetupAttachment(RootComponent);
}

void AVR_ChronomangerBase::BeginPlay()
{
	Super::BeginPlay();
	if (!bUseDayNightCycle)return;
	UpdateTimeOfDayRef();
	UpdateDayCurrentOfYear();
	CalculateDayLenght();
	InitSkySphereMaterial();
	MaterialSkysphere->SetVectorParameterValue("MoonBasicSetting", FVector4(MoonScale / 10, MoonRotation, MoonBrightness));
}

void AVR_ChronomangerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bUseDayNightCycle)return;
	UpdateTime(DeltaTime);
	UpdateTimeOfDayRef();
	UpdateRotationSunMoon();
}

void AVR_ChronomangerBase::UpdateFromSave_Implementation()
{
}

FVR_SaveActorData AVR_ChronomangerBase::GetSaveData_Implementation()
{
	TArray<FString> TimeCurrent;
	TimeCurrent.Add(CurrentTime.GetSaveString());

	return FVR_SaveActorData(GetActorTransform(), bWasSpawned, AVR_ChronomangerBase::StaticClass(), TimeCurrent);
}

void AVR_ChronomangerBase::SetActorTimerSaveData_Implementation(const TArray<FString>& RawData)
{
	int i = 0;
	TArray<FString> Parts;

	for (auto d : RawData)
	{
		Parts.Empty();
		switch (i)
		{
		case 0:
			Parts = ChopString(d, '|');
			CurrentTime.UpdateFromSaveString(Parts);
			break;
		default:
			Debug::Print(TEXT("ASGRegrowingHarvestActorBase::SetActorRawSaveData_Implementation Unexpected indec operator"));
			break;
		}
		i++;
	}
}

void AVR_ChronomangerBase::InitSkySphereMaterial()
{
	UMaterialInterface* BaseMaterial = LoadObject<UMaterialInterface>(
		nullptr,
		TEXT("/Game/DEV_/Materials/Sky/MI_DynamicSkySphere.MI_DynamicSkySphere"));
	MaterialSkysphere = SM_SkySphere->CreateDynamicMaterialInstance(0, BaseMaterial);
	//UMaterialInterface* BaseMaterial = SM_SkySphere->GetMaterial(0);
	//MaterialSkysphere = UMaterialInstanceDynamic::Create(BaseMaterial, this);
}



void AVR_ChronomangerBase::UpdateRotationSunMoon()
{
	if (!IsValid(DailySunAndMoonLightRotation) || !IsValid(MoonDirectionalLight) || !IsValid(SunDirectionalLight))
	{
		return;
	}
	//if(!IsValid(AnnualSunAndMoonLightRotation))
	//{

	//	DailySunAndMoonLightRotation->FloatCurves[1].UpdateOrAddKey(300.f, 0.f);
	//}

	FLinearColor ColorAsRotation = DailySunAndMoonLightRotation->GetUnadjustedLinearColorValue(CurrentTimeOfDay);
	DEBUG_Rotation = ColorAsRotation.R;
	VisibilitySunOrMoon();
	if (IsDay())
	{
		FRotator NewRot(ColorAsRotation.R, 0, 0);
		SunDirectionalLight->SetWorldRotation(NewRot);
		SunDirectionalLight->SetIntensity(ColorAsRotation.B);
		UpdateDayLight();
		SkyLight->SetIntensity(ColorAsRotation.A);
	}
	else
	{
		FRotator NewRot(ColorAsRotation.R, 0, 0);
		MoonDirectionalLight->SetWorldRotation(NewRot);
		MoonDirectionalLight->SetIntensity(ColorAsRotation.G);
		UpdateNightLight();
		SkyLight->SetIntensity(ColorAsRotation.A);
	}

}

void AVR_ChronomangerBase::UpdateDayLight()
{
	FLinearColor ColorDayValue = SunLightSettingsBasic->GetUnadjustedLinearColorValue(CurrentTimeOfDay);
	SunDirectionalLight->SetTemperature(ColorDayValue.A);
	SunDirectionalLight->SetLightColor(ColorDayValue);
	SkyAtmosphere->SetRayleighScattering(FLinearColor(0.08f, 0.339f, 1, 1));
	SkyAtmosphere->SetMultiScatteringFactor(1);
	MaterialSkysphere->SetScalarParameterValue("IsStarVisibility",0);
	MaterialSkysphere->SetScalarParameterValue("IsMoonVisibility", 0);
}

void AVR_ChronomangerBase::UpdateNightLight()
{
	FLinearColor ColorNightValue = MoonLightSettingsBasic->GetUnadjustedLinearColorValue(CurrentTimeOfDay);
	MoonDirectionalLight->SetTemperature(ColorNightValue.A);
	MaterialSkysphere->SetVectorParameterValue("MoonTint", ColorNightValue);
	SkyAtmosphere->SetRayleighScattering(FLinearColor(0.009f, 0.039f, 0.135, 1));
	SkyAtmosphere->SetMultiScatteringFactor(0.5);
	MaterialSkysphere->SetScalarParameterValue("IsStarVisibility",1);
	MaterialSkysphere->SetScalarParameterValue("IsMoonVisibility",1);
}

bool AVR_ChronomangerBase::IsDay() const
{
	return Drawn <= CurrentTimeOfDay && CurrentTimeOfDay <= Dusk;
}

bool AVR_ChronomangerBase::IsNight() const
{
	return !IsDay();
}

void AVR_ChronomangerBase::VisibilitySunOrMoon()
{
	MoonDirectionalLight->SetVisibility(IsNight());
	SunDirectionalLight->SetVisibility(IsDay());
}

void AVR_ChronomangerBase::UpdateTime(const float& Deltatime)
{
    TimeDecay -= Deltatime;
    if (TimeDecay <= 0)
    {
        AdvanceMinute();
        TimeDecay = MinuteLenght;
    }
}

void AVR_ChronomangerBase::AdvanceMinute()
{
	bTimeWasUpdated = true;
	CurrentTime.Minute++;
    if (CurrentTime.Minute > 59)
    {
		CurrentTime.Minute = 0;
        AdvanceHour();
    }
}

void AVR_ChronomangerBase::AdvanceHour()
{
	bTimeWasUpdated = true;
	CurrentTime.Hour++;
    if (CurrentTime.Hour > 23)
    {
		CurrentTime.Hour = 0;
        AdvanceDay();
    }
}

void AVR_ChronomangerBase::AdvanceDay()
{
	bTimeWasUpdated = true;
	AddDayOfYear();
	CurrentTime.Day++;
	switch (CurrentTime.Month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (CurrentTime.Day > 31)
		{
			CurrentTime.Day = 1;
			AdvanceMonth();
		}
		break;
	case 2:
		if ((CurrentTime.Year % 4 == 0 && CurrentTime.Year % 100 != 0) || (CurrentTime.Year % 400 == 0))
		{
			if (CurrentTime.Day > 29)
			{
				CurrentTime.Day = 1;
				AdvanceMonth();
			}
			break;
		}
		if (CurrentTime.Day > 28)
		{
			CurrentTime.Day = 1;
			AdvanceMonth();
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (CurrentTime.Day > 30)
		{
			CurrentTime.Day = 1;
			AdvanceMonth();
		}
		break;
	default:
		//TODO:: log invalid month state
		break;
	}
}

void AVR_ChronomangerBase::AdvanceMonth()
{
	bTimeWasUpdated = true;
	CurrentTime.Month++;
	if (CurrentTime.Month > 12)
	{
		CurrentTime.Month = 1;
		AdvanceYear();
	}
}

void AVR_ChronomangerBase::AdvanceYear()
{
	bTimeWasUpdated = true;
	CurrentTime.Year++;
}

void AVR_ChronomangerBase::UpdateDayCurrentOfYear()
{
	int DayCurrentOfYear = 0;
	const int DayInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	for (int i = 0; i < CurrentTime.Month - 1; i++)
	{
		DayCurrentOfYear += DayInMonth[i];
	}
	if (CurrentTime.Month > 2 &&
		((CurrentTime.Year % 4 == 0 && CurrentTime.Year % 100 != 0) || (CurrentTime.Year % 400 == 0)))
	{
		DayCurrentOfYear += 1;
	}
	CurrentTime.DayOfYear = DayCurrentOfYear + CurrentTime.Day;
}

void AVR_ChronomangerBase::CalculateDayLenght()
{
    MinuteLenght = (DayLengthInMinutes * 60) / 1440;
}

void AVR_ChronomangerBase::UpdateTimeOfDayRef()
{
	CurrentTimeOfDay = CurrentTime.Hour * 60 + CurrentTime.Minute;
}

void AVR_ChronomangerBase::AddDayOfYear()
{
	if (((CurrentTime.Year % 4 == 0 && CurrentTime.Year % 100 != 0) || (CurrentTime.Year % 400 == 0)) ? CurrentTime.DayOfYear == 366 : CurrentTime.DayOfYear == 365)
	{
		CurrentTime.DayOfYear = 0;
	}
	CurrentTime.DayOfYear++;
}
