// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Parallel/ParallelCharacter.h"
#include "UObject/NoExportTypes.h"
#include "Resource.h"
#include "ParallelTargetType.generated.h"

/**
 * class used to determine ability targets
 */

class AParallelCharacter;

UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class PARALLEL_API UParallelTargetType : public UObject
{
	GENERATED_BODY()

	public:
	UParallelTargetType(){}

	/** Called to determine targets to apply gameplay effects to */
	UFUNCTION(BlueprintNativeEvent)
    void GetTargets(AParallelCharacter* TargetingCharacter, TArray<FHitResult>& OutHitResults, TArray<AActor*>& OutActors) const;

	

};

