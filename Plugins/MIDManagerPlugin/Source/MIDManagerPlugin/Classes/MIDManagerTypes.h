// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"

#include "Engine/DataTable.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialLayersFunctions.h"

#include "MIDManagerTypes.generated.h"

/**
 * This holds all of the data you need to change MIDs on the fly.
 */
USTRUCT(BlueprintType,Blueprintable)
struct MIDMANAGERPLUGIN_API FMIDWrapper : public FTableRowBase
{
	GENERATED_BODY()

private:

	UPrimitiveComponent* CurrentComponent;

	UMaterialInstanceDynamic* DynMaterial;

	bool Initialized = false;

public:

	//Returns true if we initialized the mid struct.
	bool IsInitialized(){return Initialized;}

	//Create and set our refs.
	bool Initialize(UPrimitiveComponent* InCurrentComponent, UMaterialInstanceDynamic* InDynMaterial)
	{
		Initialized = false;
		if (InCurrentComponent)
		{
			SetCurrentComponent(InCurrentComponent);
			if (InDynMaterial)
			{
				SetDynMaterial(InDynMaterial);
			}
			else
			{
				SetDynMaterial(CreateDynMaterial(InCurrentComponent));		
			}
			ApplyScalars();
			ApplyTextures();
			ApplyColors();
			Initialized = true;
			return IsInitialized();
		}
		return IsInitialized();
	}

	//Get our current component ref.
	UPrimitiveComponent* GetCurrentComponent() { return CurrentComponent; }

	//Get our dyn material ref.
	UMaterialInstanceDynamic* GetDynMaterial() { return DynMaterial; }

	//Set the current component ref.
	UPrimitiveComponent* SetCurrentComponent(UPrimitiveComponent* InCurrentComponent) { CurrentComponent = InCurrentComponent; return GetCurrentComponent(); }

	//Set the dyn material ref.
	UMaterialInstanceDynamic* SetDynMaterial(UMaterialInstanceDynamic* InDynMaterial) { DynMaterial = InDynMaterial; return GetDynMaterial(); }

	//Create the dyn material from our base material.
	UMaterialInstanceDynamic* CreateDynMaterial(UObject* Outer) { DynMaterial = UMaterialInstanceDynamic::Create(BaseMaterial,Outer); return GetDynMaterial(); }

	//Apply the stored scalar parameters to our stored dyn material.
	void ApplyScalars()
	{
		for (auto& scalar : Scalars)
		{
			GetDynMaterial()->SetScalarParameterValueByInfo(scalar.ParameterInfo, scalar.ParameterValue);
		}
	}

	//Apply the stored texture parameters to our stored dyn material.
	void ApplyTextures()
	{
		for (auto& texture : Textures)
		{
			GetDynMaterial()->SetTextureParameterValueByInfo(texture.ParameterInfo, texture.ParameterValue);
		}
	}

	//Apply the stored color parameters to our stored dyn material.
	void ApplyColors()
	{
		for (auto& color : Colors)
		{
			GetDynMaterial()->SetVectorParameterValueByInfo(color.ParameterInfo, color.ParameterValue);
		}
	}

	/**
     * Name for JSON serialization. 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMIDWrapper")
		FName Name;

	/**
	 * The base material for the component.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMIDWrapper")
		UMaterialInterface* BaseMaterial;

	/**
	 * This can be used to force a specific index for the MID. Leave at <0 to apply to all materials.
	 * DEPRECATED
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMIDWrapper")
		int32 OverrideIndex;

	/**
	 * Scalar parameter values.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMIDWrapper")
		TArray<FScalarParameterValue> Scalars;

	/**
	 * Texture parameter values.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMIDWrapper")
		TArray<FTextureParameterValue> Textures;

	/**
	 * Vector parameter values.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMIDWrapper")
		TArray<FVectorParameterValue> Colors;

	FMIDWrapper()
	{
		Name = "MIDWrapper_";		
		BaseMaterial = nullptr;
		OverrideIndex = -1;
		Scalars.Add(FScalarParameterValue());
		Textures.Add(FTextureParameterValue());
		Colors.Add(FVectorParameterValue());
	}

	FMIDWrapper(
		FName InName,
		UMaterialInterface* InBaseMaterial,
		TArray<FScalarParameterValue> InScalars,
		TArray<FTextureParameterValue> InTextures,
		TArray<FVectorParameterValue> InColors,
		int32 InOverrideIndex = -1
	)
	{
		Name = InName;
		BaseMaterial = InBaseMaterial;
		OverrideIndex = InOverrideIndex;
		Scalars = InScalars;
		Textures = InTextures; 
		Colors = InColors;
	}

};