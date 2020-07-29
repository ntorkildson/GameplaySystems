// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "DamageDealingInt.generated.h"

UINTERFACE(MinimalAPI)
class  UDamageDealingInt : public UInterface
{
	GENERATED_BODY()

};


class PARALLEL_API IDamageDealingInt
{
	GENERATED_BODY()

public:
	
	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interactable")
    virtual float OnHealthChanged(float ChangedAmount) const;
	//virtual float OnHealthChanged_Implementation(float ChangedAmount) const;
	virtual float OnDamaged();
	
	virtual bool ReactToTrigger();

	
};