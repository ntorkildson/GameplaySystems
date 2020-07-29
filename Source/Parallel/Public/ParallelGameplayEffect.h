// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "ParallelGameplayEffect.generated.h"

/**
 * 
 */
UCLASS()
class PARALLEL_API UParallelGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

	UParallelGameplayEffect();

	FText ItemName;

	void SetWeaponStats();
	
	virtual void PostInitProperties() override;

	
};

