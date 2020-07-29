// Fill out your copyright notice in the Description page of Project Settings.


#include "Currency.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

#include "Parallel/ParallelCharacter.h"


UCurrency::UCurrency()
{
    //set everything to zero
}



void UCurrency::PreAttributeChange(const FGameplayAttribute &Attribute, float &NewValue)
{
    //TODO: if we want to keep attribute % if max health changes while current health does not, update it here
    Super::PreAttributeChange(Attribute, NewValue);

}

void UCurrency::PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data)
{
    Super::PostGameplayEffectExecute(Data);
    //cant go negative, max count will be effectively max stacks if we want to do that?
    
    if(Data.EvaluatedData.Attribute == GetWoodAttribute())
    {
        SetWood(FMath::Clamp<float>(GetWood(), 0.f, 9999.0f));
    }
    else if(Data.EvaluatedData.Attribute == GetIronAttribute())
    {
        SetIron(FMath::Clamp<float>(GetWood(), 0.f,9999.0f));
    }
    else if(Data.EvaluatedData.Attribute == GetStoneAttribute())
    {
        SetStone(FMath::Clamp<float>(GetStone(),0.f,9999.0f));
    }
    
}


void UCurrency::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    /*Basic resources*/
    DOREPLIFETIME_CONDITION_NOTIFY(UCurrency, Stone, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UCurrency, Wood, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UCurrency, Iron, COND_None, REPNOTIFY_Always);    
    

}

void UCurrency::OnRep_Iron(const FGameplayAttributeData& OldIron)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCurrency, Iron,OldIron);
}

void UCurrency::OnRep_Stone(const FGameplayAttributeData& OldStone)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCurrency, Stone,OldStone);

}

void UCurrency::OnRep_Wood(const FGameplayAttributeData& OldWood)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UCurrency, Wood,OldWood);
}


