// Fill out your copyright notice in the Description page of Project Settings.


#include "MIDManagerComponent.h"

// Sets default values for this component's properties
UMIDManagerComponent::UMIDManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMIDManagerComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UMIDManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMIDManagerComponent::Server_MIDChange_Implementation(UPrimitiveComponent* InComp, FMIDWrapper InMID)
{
	if (InComp)
	{
		CurrentMID.Add(InComp,InMID);
		if (!GetOwner()->GetNetMode() == NM_DedicatedServer)
		{
			//Only run changes if not a dedicated server. You can remove this condition if needed, but it shouldn't be necessary as this is purely visual.
			DoMIDChange(InComp);
		}
		Multicast_MIDChange(InComp,InMID);
	}
}

bool UMIDManagerComponent::Server_MIDChange_Validate(UPrimitiveComponent* InComp, FMIDWrapper InMID){return true;}

void UMIDManagerComponent::Multicast_MIDChange_Implementation(UPrimitiveComponent* InComp, FMIDWrapper InMID)
{
	if (InComp)
	{
		CurrentMID.Add(InComp,InMID);
		DoMIDChange(InComp);
	}
}

void UMIDManagerComponent::DoMIDChange(UPrimitiveComponent* InComp )
{
	FString temp;
	if (InComp)
	{
		//Lazily reinit MID each time. You 'might' be able to optimize this by checking and applying updates, but I doubt it.
		UMIDManagerFunctions::CreateMID(InComp,GetMIDForComponent(InComp),nullptr,temp);
	}
}

void UMIDManagerComponent::ChangeMIDs(UPrimitiveComponent* InComp, FDataTableRowHandle InMIDTable)
{
	if (InComp)
	{
		const UDataTable* table = InMIDTable.DataTable;
		if (table && InMIDTable.RowName != "None" && InMIDTable.RowName != "")
		{
			//Validate everything, then start the changes.
			SetMIDs(InComp, *table->FindRow<FMIDWrapper>(InMIDTable.RowName, ""));
		}
	}
}

void UMIDManagerComponent::SetMIDs(UPrimitiveComponent* InComp, FMIDWrapper InMID)
{
	//Set our MID value, then start our change on the server.
	CurrentMID.Add(InComp,InMID);
	Server_MIDChange(InComp,GetMIDForComponent(InComp));
}
