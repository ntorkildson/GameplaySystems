// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// create references to character
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*
void UInventoryComponent::EquipItem_Implementation(AParallelItem* ItemToEquip)
{
	
	switch (ItemToEquip->ItemLocation)
	{
		case EItemLocation::PrimaryWeapon:
			break;
		case EItemLocation::Chest:
			break;
		case EItemLocation::Head:
			break;
		
	}
	
	if(ItemToEquip->ItemLocation == EItemLocation::PrimaryWeapon)
	{
		
	}
	
	//check ItemToEquip.ItemLocation and equip it to that spot
	//check to see if we have an item there first
	//if we do, remove it and add it to the inventory
	//spawn ItemToEquip meshes
	//attach them to the player
	//giveSpecificAbility(ItemToEquip->GrantedAbility
	//do for secondary/tertiary abilities and passives/auras
	//add stats to player stat system.
	
	
	
	//check item slot location and apply stuff accordingly
	if(ItemToEquip->GrantedAbility)
	{
		//PrimaryWeapon = nullptr; //temporary instead of swapping stuff out.
		//PrimaryWeapon = ItemToEquip->GrantedAbility;
		//GiveSpecificAbility(PrimaryWeapon);
		//secondary weapon effect(aim or something)
		//tertiary weapon effect if applicable
		
		//grant any equippable attributes
		//ItemToEquip->GrantedAttributes;
			
		//Check for passive abilities (auras and things) to give to the player
		//ItemToEquip->PassiveAbilities;
		
	}
	
}

bool UInventoryComponent::EquipItem_Validate(AParallelItem* ItemToEquip)
{
	return true;
}

void UInventoryComponent::PickupItem_Implementation(AParallelItem* ItemToPickup)
{
	//check to see if we have one already and if its stackable
	if(Inventory.Contains(ItemToPickup) && ItemToPickup->bIsStackable)
	{
		int32 index;
		Inventory.Find(ItemToPickup,index);
		//we have the item and its stackable, so increase the quantity we have.
		Inventory[index]->ItemQty += ItemToPickup->ItemQty;
	}
	else
	{
		Inventory.Add(ItemToPickup);
	}
}

bool UInventoryComponent::PickupItem_Validate(AParallelItem* ItemToPickup)
{
	return true;
}

*/
/*
void UInventoryComponent::AddItemToInventory_Implementation(AParallelItem* ItemToAdd, int32 InventoryLocation)
{
	//PlayerInventory.Add(ItemToAdd);
	//make sure the item that was passed into this is destroyed
}

bool UInventoryComponent::AddItemToInventory_Validate(AParallelItem* ItemToAdd, int32 InventoryLocation)
{
	return true;
}

*/

