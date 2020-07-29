// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneticAlgorithm.h"

// Sets default values for this component's properties
UGeneticAlgorithm::UGeneticAlgorithm()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGeneticAlgorithm::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGeneticAlgorithm::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FGenotype UGeneticAlgorithm::BabyMaker(FGenotype& Mom, FGenotype& Dad)
{
	//have to run it for every stat...not great
	FGenotype Child;
	Child.MaxHealth = CrossOver(Mom.MaxHealth, Dad.MaxHealth);
	Child.MaxHealth = Mutation(Child.MaxHealth,Child.MaxPertubation,Child.MutationRate);
	

	//Alternative method assuming actual keys are created previously
	/*
	FGenotype Child2;
	for(int i =0; i < Mom.Stats.Num(); i++)
	{
		Child2.Stats[i] = CrossOver(Mom.Stats[i], Dad.Stats[i]);
		//Child.Stats[i] = Mutation(Child.Stats[i],2.0f, 3);
	}
	
	return Child2;
	*/
	return Child;
}

