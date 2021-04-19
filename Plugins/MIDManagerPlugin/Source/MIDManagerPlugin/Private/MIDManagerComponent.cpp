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

void UMIDManagerComponent::Server_MIDChange(UPrimitiveComponent* InComp, FMIDWrapper InMID)
{
	if (InComp)
	{
		CurrentMID[InComp] = InMID;
		if (GetOwner()->GetLocalRole() >= ROLE_Authority)
		{
			DoMIDChange(InComp);
		}
		Multicast_MIDChange(InComp,InMID);
	}
}

void UMIDManagerComponent::Multicast_MIDChange(UPrimitiveComponent* InComp, FMIDWrapper InMID)
{
	if (InComp)
	{
		CurrentMID[InComp] = InMID;
		DoMIDChange(InComp);
	}
}

void UMIDManagerComponent::DoMIDChange(UPrimitiveComponent* InComp )
{
	FString temp;
	if (InComp)
	{
		UMIDManagerFunctions::CreateMID(InComp,GetMIDForComponent(InComp),nullptr,temp);
	}
}

void UMIDManagerComponent::ChangeMIDs(UPrimitiveComponent* InComp, FDataTableRowHandle InMIDTable)
{
	if (InComp)
	{
		const UDataTable* table = InMIDTable.DataTable;
		if (table)
		{
			SetMIDs(InComp, *table->FindRow<FMIDWrapper>(InMIDTable.RowName, ""));
		}
	}
}

void UMIDManagerComponent::SetMIDs(UPrimitiveComponent* InComp, FMIDWrapper InMID)
{
	CurrentMID[InComp] = InMID;
	Server_MIDChange(InComp,GetMIDForComponent(InComp));
}
