// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "ParallelAbilityTypes.generated.h"


USTRUCT(BlueprintType)
struct FParallelGameplayEffectContainer
{
	GENERATED_BODY()
public:
	FParallelGameplayEffectContainer(){}

	//TODO: add this targeting type to our project
	//UPROPERTY(EditAnywhere, Category= "Gameplay Effects")
	//TSubclassOf<UParallelTargetType> TargetType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClass;
	
};

USTRUCT(BlueprintType)
struct FParallelGameplayEffectContainerSpec
{
	GENERATED_BODY()
public:
	FParallelGameplayEffectContainerSpec(){}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	FGameplayAbilityTargetDataHandle TargetData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffectContainer")
	TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;
	
	void AddTarget(const TArray<FHitResult>& Hitresults, const TArray<AActor*>& TargetActors);

	
};


