// Fill out your copyright notice in the Description page of Project Settings.


#include "ParallelItem.h"

AParallelItem::AParallelItem()
{
    SetReplicates(true);
}

void AParallelItem::GiveBonusStats()
{
    //take all our stats and grant them to the player somehow...
    BonusStats->PhysicalStrength;
    
}



float AParallelItem::GetIronValue()
{
  if(!CurrencyAmount)
        return -1;
    return CurrencyAmount->GetIron();
    
}

float AParallelItem::GetStoneValue()
{
    if(!CurrencyAmount)
        return -1;
    return CurrencyAmount->GetStone();
}

float AParallelItem::GetWoodValue()
{
    if(!CurrencyAmount)
        return -1;
    return CurrencyAmount->GetWood();
}

