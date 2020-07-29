// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Currency.h"
#include "DamageDealingInt.h"
#include "MainAttributes.h"
#include "MeshAttributeArray.h"
#include "ParallelActorPickup.h"
#include "DamageDealingInt.h"


#include "ParallelCharacter.generated.h"

class AParallelItem;


UCLASS(config=Game)
class AParallelCharacter : public ACharacter, public IAbilitySystemInterface, public IDamageDealingInt
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

		
public:

	AParallelCharacter();

	virtual void BeginPlay();

    virtual void PossessedBy(AController* NewController) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
    //Attributes here
    // Our ability system component.
    UPROPERTY(BlueprintReadOnly, Category = "Character Base | Ability System Component")
    class UAbilitySystemComponent* AbilitySystemComponent;

    // Helper function to get our ability system component (Used by the IAbilitySystemInterface).
    UFUNCTION(BlueprintPure, Category = "Character Base | Ability System Component")
    UAbilitySystemComponent* GetAbilitySystemComponent() const override;



	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "Character Base | Ability System")
	void GiveAbilities(AParallelItem* ItemWithAbilities);

	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "Character Base | Ability System")
	void RemoveAbilities(AParallelItem* ItemWithAbilities);
	
	//called on death or when we lose everything in our inventory
	UFUNCTION(BlueprintCallable, Server	, Reliable, WithValidation, Category = "Character Base | Abilitiy System ")
	void RemoveAllAbilities();
	
	//removes a specific ability for when players drop/sell/whatever items from inventory
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = " Character Base | Ability System")
	void RemoveSpecificAbility(TSubclassOf<UGameplayAbility> AbilityToRemove);
	
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "Character Base | Ability")
	void GiveSpecificAbility(TSubclassOf<UGameplayAbility> AbilityToGive);

	

    //default Attributes  not actually needed if we are using gameplay effects to trigger stats....
    UPROPERTY()
    UMainAttributes* AttributeSet;

		
	//all currency items will be stored here...need a lot of getter functions unfortunately.
	UPROPERTY()
	UCurrency* CurrencySet;
	
    //gameplayEffect with the default stats we have as a blank character
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character Base | Defaults")
    TSubclassOf<class UGameplayEffect> DefaultAttributeReference;
		
	//used for auras, passive regen, etc.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character Base | Combat")
	TArray<TSubclassOf<UGameplayAbility>> PassiveAbilities;
	
	
    //initializes player stats
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
    void InitializeStats();
	
	
    //TODO: add the rest of the stats for easy getters
    UFUNCTION(BlueprintCallable, Category = "Attributes")
    float GetLife();

	UFUNCTION(BlueprintCallable,Category="Attributes")
	float GetMaxLife();
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMana();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMaxMana();
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetEnergy();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetMaxEnergy();
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetPhysicalStrength();
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetPhysicalDexterity();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetPhysicalEndurance();

	UFUNCTION(BlueprintCallable,Category = "Attributes")
	float GetMinDamage();

	UFUNCTION(BlueprintCallable,Category = "Attributes")
	float GetCritChance();

	UFUNCTION(BlueprintCallable,Category = "Attributes")
	float GetCritMultiplier();

	UFUNCTION(BlueprintCallable,Category = "Attributes")
	float GetAttackSpeed();

	
/************************Currency  SYSTEM HERE**********************************/

	//TODO: add the rest of the rescource getters
	UFUNCTION(BlueprintCallable, Category = "Currency")
	float GetWood();
	
	UFUNCTION(BlueprintCallable, Category = "Currency")
	float GetIron();

	UFUNCTION(BlueprintCallable,Category = "Currency")
	float GetStone();
	
/************************INVENTORY SYSTEM HERE**********************************/
	

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FName WeaponSocket;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory",Replicated,Transient)
	TArray<AParallelItem*> Inventory;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Character Base | Combat",Replicated)
	class AParallelItem* CurrentWeapon;

	class AParallelItem* PreviousWeapon;
	
	//Item goes from inventory to being equipped
	UFUNCTION(BlueprintCallable, Category = "Inventory")

	void EquipItem(AParallelItem* ItemToEquip);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory", Server, Reliable, WithValidation)
	void ServerEquipItem(AParallelItem* ItemToEquip);

	void SetCurrentWeapon(class AParallelItem* NewWeapon, class AParallelItem* LastWeapon = nullptr);
	
	
	UFUNCTION(BlueprintCallable, Category = "Inventory", Server, Reliable, WithValidation)
	void RemoveItem(AParallelItem* ItemToRemove);
	
	
	/* Update the weapon mesh to the newly equipped weapon, this is triggered during an anim montage.
	NOTE: Requires an AnimNotify created in the Equip animation to tell us when to swap the meshes. */
	UFUNCTION(BlueprintCallable, Category = "Animation")
    void SwapToNewWeaponMesh();

	
	//removes equipped Item and adds to inventory
	UFUNCTION(BlueprintCallable, Category = "Inventory", Server, Reliable, WithValidation)
	void UnEquipItem(AParallelItem* ItemToUnEquip);
	
		
	//grabs item from world and adds to inventory
	UFUNCTION(BlueprintCallable, Category = "Inventory", Server, Reliable, WithValidation)
	void PickupItem(class AParallelItem* ItemToPickup);

	
	//removes item from inventory and spawns into the world
	UFUNCTION(BlueprintCallable, Category = "Inventory", Server, Reliable, WithValidation)
	void DropItem(AParallelItem* ItemToDrop);
	
	
	
	//TODO: rework this
	void InteractWith();

	UFUNCTION(Server,Reliable,WithValidation)
	void ServerInteractWith();

	AParallelActorPickup* GetItemInView();
	
	/**************Damage stuff here**************/
	//for use when we take damage
	virtual float OnDamaged() override;

	//used anytime our health changes(healing or damage)
	void OnHealthChange();
	
	
	void OnEnergyChange();

	void OnPhysicalStrengthChange();

	void OnPhysicalDexterityChange();

	void OnPhysicalEnduranceChange();

		
    //what happens on death
    void OnDeath();
    /*
     * TODO:
     * remove abilities
     * play death animation/sound
     * drop loot/experience
     *
     * unpossess player controller
     * spawn new character(naked)
     * reinitalize player stats and stuff
     * possess new character
     * continue playing
     * */

	


	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;



protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

