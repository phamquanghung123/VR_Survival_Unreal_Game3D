// Fill out your copyright notice in the Description page of Project Settings.


#include "VR_Utils.h"

TArray<FString> ChopString(FString Source, char split)
{
	TArray<FString> Ret;
	FString push;
	for (int i = 0; i < Source.Len(); i++)
	{
		if (Source[i] == split)
		{
			Ret.Add(push);
			push.Empty();
		}
		else
		{
			push += Source[i];
			if (i == ((int)Source.Len() - 1))
			{
				Ret.Add(push);
			}
		}
	}
	return Ret;
}