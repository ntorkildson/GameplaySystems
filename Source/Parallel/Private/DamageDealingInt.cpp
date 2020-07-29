// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageDealingInt.h"

float IDamageDealingInt::OnHealthChanged(float ChangedAmount) const
{
  //  UE_LOG(LogTemp,Error,TEXT("Interface Called, Life changed by: %f"),ChangedAmount);

    return ChangedAmount;
}

float IDamageDealingInt::OnDamaged()
{
    return -1.f;
}

bool IDamageDealingInt::ReactToTrigger()
{
    return false;
}


