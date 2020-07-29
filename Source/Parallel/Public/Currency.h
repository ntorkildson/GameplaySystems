// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "Currency.generated.h"


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * TODO: is this really the best way to do this? or is an inventory better? hmmmm.....
 */

UCLASS()
class PARALLEL_API UCurrency : public UAttributeSet
{
    GENERATED_BODY()

public:

    UCurrency();

    // AttributeSet Overrides
    virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

 
    /*Basic building is similar to ark / 7 days to die / dont starve */
    UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Currency | Basic", ReplicatedUsing = OnRep_Stone)
    FGameplayAttributeData Stone;
    ATTRIBUTE_ACCESSORS(UCurrency, Stone)

    UFUNCTION()
    virtual void OnRep_Stone(const FGameplayAttributeData& OldStone);
    
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency | Basic" , ReplicatedUsing = OnRep_Wood)
    FGameplayAttributeData Wood;
    ATTRIBUTE_ACCESSORS(UCurrency, Wood);
    
    UFUNCTION()
    virtual void OnRep_Wood(const FGameplayAttributeData& OldWood);

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Currency | Basic" , ReplicatedUsing = OnRep_Iron)
    FGameplayAttributeData Iron;
    ATTRIBUTE_ACCESSORS(UCurrency, Iron);

   UFUNCTION()
   virtual void OnRep_Iron(const FGameplayAttributeData& OldIron);

   //TODO: implement basic crafting materials

  //TODO: implement rare/uncommon crafting materials

  
 
   
    /*fiber - used for ropes and things
     *thatch - used for basic roofing or something
     *sulfer - used for explosives into late game
     *silk	- probably dont need this
     *various metals - used for different things
     *gems - used for different things(elemental)
     *sand - used for glass
     *flint -used for whatever idk
     *clay 	-used for pottery?
     *charcoal	-used for burning
     *
    */
    /*Uncommon currency is crafted from the previous rescources or dropped by rare monsters*/
    /*
     * 
     */


    /*Rare currency is like Path of Exile, used exclusively for crafting and is the made tradable currency we will use*/
    /*
     *found or crafted baased on the previous tier, rescource sink is effectively what this is
    */
 
};
