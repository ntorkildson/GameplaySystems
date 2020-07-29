// Fill out your copyright notice in the Description page of Project Settings.


#include "ParallelGameplayEffect.h"

UParallelGameplayEffect::UParallelGameplayEffect()
{
    /*TODO: UI Data and the attributes can be linked and passed to the UI system*/
    
}

void UParallelGameplayEffect::SetWeaponStats()
{
    /*we need to create getters/setters for all the attrubtes we want to share with the player, this is a tentative l ist.*/
    
    
    
}

void UParallelGameplayEffect::PostInitProperties()
{
    Super::PostInitProperties();
    UE_LOG(LogTemp,Warning,TEXT(" Hi from gameplay effect class "));

}
