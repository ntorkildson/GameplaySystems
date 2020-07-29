// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MainAttributes.generated.h"


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**  TODO: WIP implementation, leaving it as is now, but needs a finalized system at some point.
 * 
 */

UCLASS()
class UMainAttributes : public UAttributeSet
{
	GENERATED_BODY()

public:

    UMainAttributes();
	
    // AttributeSet Overrides
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Attributes | Actions", ReplicatedUsing = OnRep_Actions)
    FGameplayAttributeData Actions;
	ATTRIBUTE_ACCESSORS(UMainAttributes, Actions)

    UFUNCTION()
    virtual void OnRep_Actions(const FGameplayAttributeData& OldHealth);


	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Attributes | Actions", ReplicatedUsing = OnRep_MaxActions)
	FGameplayAttributeData MaxActions;
	ATTRIBUTE_ACCESSORS(UMainAttributes, MaxActions)

    UFUNCTION()
    virtual void OnRep_MaxActions(const FGameplayAttributeData& OldMaxActions);

    UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Attributes | BaseStats", ReplicatedUsing = OnRep_Life)
    FGameplayAttributeData Life;
    ATTRIBUTE_ACCESSORS(UMainAttributes, Life)

    UFUNCTION()
    virtual void OnRep_Life(const FGameplayAttributeData& OldMaxActions);

	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Attributes | BaseStats", ReplicatedUsing = OnRep_Life)
    FGameplayAttributeData MaxLife;
	ATTRIBUTE_ACCESSORS(UMainAttributes, MaxLife)

    UFUNCTION()
    virtual void OnRep_MaxLife(const FGameplayAttributeData& OldMaxActions);
	
    /*spell resource system*/
    UPROPERTY(BLueprintReadWrite, EditAnywhere, Category = "Attributes|Base Stats" , ReplicatedUsing = OnRep_Mana)
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(UMainAttributes, Mana)

    UFUNCTION()
    virtual void OnRep_Mana();

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category	="Attributes|Base Stats", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMainAttributes,MaxMana)

	UFUNCTION()
	virtual void OnRep_MaxMana();
		
    /*physical attack resource system*/
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes |Base Stats", ReplicatedUsing = OnRep_Energy)
    FGameplayAttributeData Energy;
    ATTRIBUTE_ACCESSORS(UMainAttributes, Energy)

    UFUNCTION()
    virtual void OnRep_Energy();


	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category	="Attributes|Base Stats", ReplicatedUsing = OnRep_MaxEnergy)
	FGameplayAttributeData MaxEnergy;
	ATTRIBUTE_ACCESSORS(UMainAttributes,MaxEnergy)

    UFUNCTION()
    virtual void OnRep_MaxEnergy();

	
    /*Physical Stats*/
    //used to calculate physical damage
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes |Physical Stats", ReplicatedUsing = OnRep_PhysicalStrength)
    FGameplayAttributeData PhysicalStrength;
    ATTRIBUTE_ACCESSORS(UMainAttributes, PhysicalStrength)

    UFUNCTION()
    virtual void OnRep_PhysicalStrength();
	
    //used to calculate dodge and physical critical strike chance/damage
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes |Physical Stats", ReplicatedUsing = OnRep_PhysicalDexterity)
    FGameplayAttributeData PhysicalDexterity;
    ATTRIBUTE_ACCESSORS(UMainAttributes, PhysicalDexterity)
	
    UFUNCTION()
    virtual void OnRep_PhysicalDexterity();

    //Used to calcuate hitpoints and resistances to physical damage
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes |Mental Stats", ReplicatedUsing = OnRep_PhysicalEndurance)
    FGameplayAttributeData PhysicalEndurance;
    ATTRIBUTE_ACCESSORS(UMainAttributes, PhysicalEndurance)

    UFUNCTION()
    virtual void OnRep_PhysicalEndurance();
    
    UPROPERTY(BlueprintReadWrite,EditAnywhere, Category ="Attributes | Base Stats", ReplicatedUsing = OnRep_MentalStrength)
    FGameplayAttributeData MentalStrength;
    ATTRIBUTE_ACCESSORS(UMainAttributes, MentalStrength)

    UFUNCTION()
    virtual void OnRep_MentalStrength();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes | Base Stats", ReplicatedUsing = OnRep_MentalDexterity)
    FGameplayAttributeData MentalDexterity;
    ATTRIBUTE_ACCESSORS(UMainAttributes, MentalDexterity)

    UFUNCTION()
    virtual void OnRep_MentalDexterity();


    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes | Base Stats", ReplicatedUsing = OnRep_MentalEndurance)
    FGameplayAttributeData MentalEndurance;
    ATTRIBUTE_ACCESSORS(UMainAttributes, MentalEndurance)

    UFUNCTION()
    virtual void OnRep_MentalEndurance();
       
	
	
    /*Combat Stats*/

	/*	
	 * MinDamage
	 * MaxDamage
	 * CritChance
	 * CritMultiplier
	 * attack speed
	 *
	 */
		
	
	//TODO: Rename to weapon damage
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes | Offense Stats", ReplicatedUsing = OnRep_BaseDamage)
	FGameplayAttributeData BaseDamage;
	ATTRIBUTE_ACCESSORS(UMainAttributes, BaseDamage)
	
	UFUNCTION()
	virtual void OnRep_BaseDamage();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes | Offense Stats", ReplicatedUsing = OnRep_CritChance)
	FGameplayAttributeData CritChance;
	ATTRIBUTE_ACCESSORS(UMainAttributes, CritChance)

	UFUNCTION()
	virtual void OnRep_CritChance();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " Attributes | Offensive Stats", ReplicatedUsing = OnRep_CritDamage)
	FGameplayAttributeData CritDamage;
	ATTRIBUTE_ACCESSORS(UMainAttributes, CritDamage)

	UFUNCTION()
	virtual void OnRep_CritDamage();
	
	//attack Speed
	//Armor Penetration flat and percentage?
	//PhysToElementalConversion - gonna be a lot of these I think...kinda sad but whatever
	//SlashingDamage
	//PenetratingDamage
	//ImpactDamage
	//Water
	//Fire
	//Air
	//Earth
	//Chaos
	//poison
	//etc

	
	
    /*Defense Stats*/
    /*
     *
     *Shield
     * DamageTakenConversionTOOtherElement
     *Armor:
		*Slashing
		*Penetrating
		*Impact
		*Water
		*Fire
		*Air
		*Earth
     *Physical / Mental Dodge/parry
     *block if applicable? or should it be player skill based?
     * 
     */
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes | Defensive Stats", ReplicatedUsing = OnRep_PhysicalArmor)
	FGameplayAttributeData PhysicalArmor;
	ATTRIBUTE_ACCESSORS(UMainAttributes, PhysicalArmor)

	UFUNCTION()
	virtual void OnRep_PhysicalArmor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes | Defensive Stats", ReplicatedUsing = OnRep_SlashingDefense)
	FGameplayAttributeData SlashingDefense;
	ATTRIBUTE_ACCESSORS(UMainAttributes, SlashingDefense)

    UFUNCTION()
    virtual void OnRep_SlashingDefense();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes | Defensive Stats", ReplicatedUsing = OnRep_PhysicalDodge)
	FGameplayAttributeData PhysicalDodge;
	ATTRIBUTE_ACCESSORS(UMainAttributes, PhysicalDodge)

	UFUNCTION()
	virtual void OnRep_PhysicalDodge();

	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
	
};
