// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GeneticAlgorithm.generated.h"

//chromosome
USTRUCT(BlueprintType)
struct FGenotype 	//Genotype can be any stats or values that we want to have be breedable
{
	GENERATED_BODY();

	//placeholder stats, can be whatever, will eventually use GAS system
	UPROPERTY(BlueprintReadWrite)
	int MaxHealth;

	UPROPERTY(BlueprintReadWrite)
	int MaxStrength;

	UPROPERTY(BlueprintReadWrite)
	int32 MutationRate;

	UPROPERTY(BlueprintReadWrite)
	int32 MaxPertubation;

	FGenotype()
	{
		MaxHealth = 0;
		MaxStrength = 0;

		MutationRate = 3;
		MaxPertubation = 2;

	}
};


template<typename GA>
GA CrossOver(GA Mom, GA Dad)
{
	return FMath::RandRange(0,2)%2 == 0 ? Dad : Mom;
	
}

//Stat to check Mutation on, %Chance to mutate, how much it mutates by
template<typename GA>
GA Mutation(GA stat, float MutationRate, GA MaxPertubation)
{
	//Check to see if there is a mutation
	if(FMath::FRandRange(0,100) <= MutationRate)
	{
		//TODO: Make this something worthwhile becuase it doesnt look right
		return FMath::RandRange(0,100) <= 50 ? stat += MaxPertubation : stat -=  MaxPertubation;
		
	}
	return stat;
}

/*Array of the total population we are referencing
 *reference to an empty array of our survivors
 * the totalFitness of the population
 * for everyone in the population check the individual fitness,
 * roll the dice to see if you get to breed or if you just die
 */
template<typename GA>
GA RouletteSelection(TArray<GA> &Population, TArray<GA> &Survivors,GA totalPopulationFitness)
{
	float Slice = rand() * totalPopulationFitness; 
	
	float PreviousProbability =0.0f;
	return rand() * totalPopulationFitness;
/*
	for(int i=0; i < Population.Num(); i++)
	{
		PreviousProbability += Population[i].Num(); //todo: make this work 
		if(PreviousProbability >= Slice)
		{
			return Population[i];
		}
			return nullptr;
	}
*/	
}


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARALLEL_API UGeneticAlgorithm : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGeneticAlgorithm();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//both parents we are breeding together, calls crossover and mutation and returns the child stats;
	UFUNCTION(BlueprintCallable, Category = "Genetic Algorithm")
	FGenotype BabyMaker(FGenotype& Mom, FGenotype &Dad);
		
	
};

