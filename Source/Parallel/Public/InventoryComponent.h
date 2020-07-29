// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParallelItem.h"

#include "Components/ActorComponent.h"

#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARALLEL_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	
	//Creates an  Inventory of whatever size
	//void InitInventory(int32 InventorySize);
	
	//Gets inventory item at specific slot
	//void GetInventoryItem(int32 ItemSlot);
	
	//Sets inventoryItem at specific slot
	//void SetInventoryItem(int32 ItemSlot);
	
	//Clear Inventory Item
	
	//Loads from the server TODO: Implement a server system that can handle this
	//LoadInventoryItems();
	
	//Saves inventory to server
	//SaveInventoryItems();
	
	/*
	UFUNCTION(BlueprintCallable,Server,Reliable, WithValidation, Category="Inventory")
	void AddItemToInventory(AParallelItem* ItemToAdd, int32 InventoryLocation = 0);

	
	UFUNCTION(BlueprintCallable,Server,Reliable, WithValidation, Category="Inventory")
	void EquipItem(AParallelItem* ItemToEquip);
	
	UFUNCTION(BlueprintCallable,Server,Reliable, WithValidation, Category="Inventory")
	void UnEquipItem(AParallelItem* ItemToUnequip);
	
	
	UFUNCTION(BlueprintCallable,Server,Reliable, WithValidation, Category="Inventory")
    void PickupItem(AParallelItem* ItemToPickup);
	
	UFUNCTION(BlueprintCallable,Server,Reliable, WithValidation, Category="Inventory")
	void DropItem(AParallelItem* ItemToDrop);
*/
	/*
	*/
	//our actual inventory
	//TODO: Replicated and owned by the server
	TArray<class AParallelItem*> Inventory;
		
};
