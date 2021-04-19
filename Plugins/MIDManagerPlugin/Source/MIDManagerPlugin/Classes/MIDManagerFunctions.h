// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "MIDManagerTypes.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "MIDManagerFunctions.generated.h"

/**
 * Wrapper for any functions that the MID manager might need.
*/
UCLASS(BlueprintType,Blueprintable)
class MIDMANAGERPLUGIN_API UMIDManagerFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public: 

	/**
	 * Initialize the MID with it's primitive comp and material instance dynamic.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static bool CreateMID(UPrimitiveComponent* InComp, FMIDWrapper InMID, UMaterialInstanceDynamic* DynMaterial, FString& OutError);

	/**
	 * Apply MIDs to all materials for the primitive component. 
	 * This iterates through all of the material slots for the component and attempts to match the InMIDs array index to the material slot index.
	 * If a match isn't found, we default to element 0.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static bool ApplyMIDs(FMIDWrapper InMID, FString& OutError);

	/**
		* Apply MIDs to all materials for the primitive component.
		* This iterates through all of the material slots for the component and attempts to match the InMIDs array index to the material slot index.
		* If a match isn't found, we default to element 0.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static bool ApplyMID(FMIDWrapper InMID, int32 Index, FString& OutError);

	/**
	 * Returns true if we initialized the mid struct.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static bool IsInitialized(FMIDWrapper MID) { return MID.IsInitialized(); }

	/**
	 * Create and set our refs.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static bool Initialize(FMIDWrapper MID, UPrimitiveComponent* InCurrentComponent, UMaterialInstanceDynamic* InDynMaterial) { return MID.Initialize(InCurrentComponent,InDynMaterial);	}

	/**
	 * Get our current component ref.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static UPrimitiveComponent* GetCurrentComponent(FMIDWrapper MID) { return MID.GetCurrentComponent(); }

	/**
	 * Get our dyn material ref.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static UMaterialInstanceDynamic* GetDynMaterial(FMIDWrapper MID) { return MID.GetDynMaterial(); }

	/**
	 * Set the current component ref.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static UPrimitiveComponent* SetCurrentComponent(FMIDWrapper MID, UPrimitiveComponent* InCurrentComponent) { return MID.SetCurrentComponent(InCurrentComponent); }

	/**
	 * Set the dyn material ref.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static UMaterialInstanceDynamic* SetDynMaterial(FMIDWrapper MID, UMaterialInstanceDynamic* InDynMaterial) { return MID.SetDynMaterial(InDynMaterial); }

	/**
	 * Create the dyn material from our base material.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static UMaterialInstanceDynamic* CreateDynMaterial(FMIDWrapper MID, UObject* Outer) { return MID.CreateDynMaterial(Outer); }

	/**
	 * Apply the stored scalar parameters to our stored dyn material.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static void ApplyScalars(FMIDWrapper MID) { MID.ApplyScalars(); }

	/**
	 * Apply the stored texture parameters to our stored dyn material.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static void ApplyTextures(FMIDWrapper MID) { MID.ApplyTextures(); }

	/**
	 * Apply the stored color parameters to our stored dyn material.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerFunctions")
		static void ApplyColors(FMIDWrapper MID) { MID.ApplyColors(); }
};
