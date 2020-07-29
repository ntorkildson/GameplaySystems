// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"


#include "Styling/SlateBrush.h"

#include "PrimaryAbility.h"
#include "Currency.h"
#include "MainAttributes.h"

#include "Parallel/Parallel.h"


#include "ParallelItem.generated.h"

/**TODO: Data assets arent good for this, we need to change to an actor
 * 	Holds our item information for when its in the players inventory
 * 	
 */




UENUM(BlueprintType)
enum class ItemSocketLocation : uint8
{
	PrimaryWeapon 	UMETA(DisplayName = "Primary"),
	SecondaryWeapon	UMETA(DisplayName = "Secondary"),
	Head			UMETA(DisplayName = "Head"),
	Chest			UMETA(DisplayName "Chest"),
	Belt			UMETA(DisplayName ="Belt"),
	Boots			UMETA(DisplayName ="Boots"),
	Shoulders		UMETA(DisplayName ="Shoulders"),
	Arms			UMETA(DisplayName = "Arms"),
	Gloves			UMETA(DisplayName ="Gloves"),
	Cape			UMETA(DisplayName = "Cape"),
};

//what ability does this item give and where does it get equipped
USTRUCT(BlueprintType)
struct FAbilityStuff
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
      EGSAbilityInputID ItemLocation;
	
	//Primary ability to give the player, typically a spell or a melee attack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    TSubclassOf<UPrimaryAbility> PrimaryAbility;

	FAbilityStuff()
	{
		ItemLocation = EGSAbilityInputID::None;
		PrimaryAbility = nullptr;
	}
};


UCLASS()
class PARALLEL_API AParallelItem : public AActor
{
	GENERATED_BODY()

public:
    AParallelItem();
	
	//item name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemName;
	
	//item description
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FText ItemDescription;
	
	//item icon
    /** Icon to display */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    FSlateBrush InventoryIcon;

	//item mesh in world
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    USkeletalMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	class USkeletalMesh* ItemMesh2;


	//Primary ability to give the player, typically a spell or a melee attack
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
    TArray<TSubclassOf<UPrimaryAbility>> Abilities;

	
	//TODO: give all items an attribute system and see if we can transfer those the character on equip.
	UPROPERTY()
	UMainAttributes* BonusStats;

	UPROPERTY()
	UCurrency* CurrencyAmount;
	
	UFUNCTION(BlueprintCallable,Category= "Item|Stats")
	void GiveBonusStats();
	
		
	/* The class to spawn in the level when dropped */
	UPROPERTY(EditDefaultsOnly, Category = "Item")
    TSubclassOf<class AParallelActorPickup> WeaponPickupClass;
	
		
	//value if we scrap or sell this item to a vendor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSubclassOf<class UGameplayEffect> SellValue;

	
	
	
	//Can we stack in the inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	bool bIsStackable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 ItemQty;
	
	//is consumable
	bool bIsConsumable;


	float GetIronValue();
	
	float GetStoneValue();

	float GetWoodValue();
	
};

