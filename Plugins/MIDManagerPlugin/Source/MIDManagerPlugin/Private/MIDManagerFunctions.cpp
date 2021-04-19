// Fill out your copyright notice in the Description page of Project Settings.


#include "MIDManagerFunctions.h"

bool UMIDManagerFunctions::CreateMID(UPrimitiveComponent* InComp, FMIDWrapper InMID, UMaterialInstanceDynamic* DynMaterial, FString& OutError)
{
	if (InComp)
	{
		//Run the structs init method.
		InMID.Initialize(InComp, DynMaterial);
		OutError = "Initialized!";
		return ApplyMIDs(InMID,OutError);
	}
	OutError = "Invalid MID Component!";
	return false;
}

bool UMIDManagerFunctions::ApplyMIDs(FMIDWrapper InMID, FString& OutError)
{
	if (InMID.IsInitialized())
	{
		//Get all materials and apply mid based on settings.
		for (int32 x = 0; x < InMID.GetCurrentComponent()->GetNumMaterials(); x++)
		{
			ApplyMID(InMID, x, OutError);
		}
		OutError = "MID applied!";
		return true;
	}
	OutError = "MID requires init!";
	return false;
}

bool UMIDManagerFunctions::ApplyMID(FMIDWrapper InMID, int32 Index,FString& OutError)
{
	if (!InMID.IsInitialized())
	{
		OutError = "MID is not initialized!";
		return false;
	}
	//Reapply all MID values and set the material index.
	InMID.ApplyScalars();
	InMID.ApplyTextures();
	InMID.ApplyColors();
	InMID.GetCurrentComponent()->SetMaterial(Index, InMID.GetDynMaterial());
	OutError = "Applied MID to InMID";
	return true;
}
