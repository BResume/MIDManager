// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/DataTable.h"

#include "MIDManagerTypes.h"
#include "MIDManagerFunctions.h"

#include "MIDManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MIDMANAGERPLUGIN_API UMIDManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMIDManagerComponent();

	/**
	 * The default data table row handle..
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MIDManagerComponent")
		FDataTableRowHandle DefaultMIDTableRow;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	//Set MID ref and properties on server.
	UFUNCTION(Server, Unreliable, WithValidation, Category = "MIDManagerComponent")
		void Server_MIDChange(UPrimitiveComponent* InComp, FMIDWrapper InMID);

	//Set MID ref and properties on all clients.
	UFUNCTION(NetMulticast, Unreliable, Category = "MIDManagerComponent")
		void Multicast_MIDChange(UPrimitiveComponent* InComp, FMIDWrapper InMID);

	void DoMIDChange(UPrimitiveComponent* InComp);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Set MID from default datatable row.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerComponent")
		void SetDefaultMIDs(UPrimitiveComponent* InComp) { ChangeMIDs(InComp,DefaultMIDTableRow); }

	/**
	 * Set MID from datatable row.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerComponent")
		void ChangeMIDs(UPrimitiveComponent* InComp,FDataTableRowHandle InMIDTable);

	/**
	 * Set MID props and replicate.
	*/
	UFUNCTION(BlueprintCallable, Category = "MIDManagerComponent")
		void SetMIDs(UPrimitiveComponent* InComp,FMIDWrapper InMID);

	/**
	 * Return the CurrentMID Map
	*/
	UFUNCTION(BlueprintPure,Category = "MIDManagerComponent")
		TMap<UPrimitiveComponent*, FMIDWrapper> GetCurrentMIDs() { return CurrentMID; }

	/**
	 * Get the MID for the given component.
	*/
	UFUNCTION(BlueprintPure,Category = "MIDManagerComponent")
		FMIDWrapper GetMIDForComponent(UPrimitiveComponent* InComp) { FMIDWrapper out;  if (InComp) { out = CurrentMID[InComp]; } return out; }

private:

	TMap<UPrimitiveComponent*,FMIDWrapper> CurrentMID;

};
