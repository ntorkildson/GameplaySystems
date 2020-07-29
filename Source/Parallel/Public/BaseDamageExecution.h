// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "BaseDamageExecution.generated.h"

/**
 * 
 */
UCLASS()
class PARALLEL_API UBaseDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	public:
	UBaseDamageExecution();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

	
};



