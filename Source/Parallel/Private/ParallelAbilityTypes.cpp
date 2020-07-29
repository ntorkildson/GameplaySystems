// Fill out your copyright notice in the Description page of Project Settings.


#include "ParallelAbilityTypes.h"


void FParallelGameplayEffectContainerSpec::AddTarget(const TArray<FHitResult>& Hitresults,
    const TArray<AActor*>& TargetActors)
{
    for(const FHitResult& HItReslt : Hitresults)
    {
        //TODO: extend this functionality to use more of the geameplayAbilityTargetData types...it kinda does it for us...
        FGameplayAbilityTargetData temp;
    }
    
}

