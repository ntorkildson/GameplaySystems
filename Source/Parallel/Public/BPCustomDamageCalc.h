// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "BPCustomDamageCalc.generated.h"

/**
 * 
 */
UCLASS()
class PARALLEL_API UBPCustomDamageCalc : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	//get gameplay effect spec and do some fancy numbers, return a flaot for the final damage;
};
