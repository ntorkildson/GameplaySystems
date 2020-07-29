// Fill out your copyright notice in the Description page of Project Settings.

#include "ParallelTargetType.h"



void UParallelTargetType::GetTargets_Implementation(AParallelCharacter* TargetingCharacter,  TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const
{
    if(!OutActors.Contains(TargetingCharacter))
    {
        OutActors.Add(TargetingCharacter);
    }
    else
        OutActors.Remove(TargetingCharacter);
}


