// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkovChain.h"

#include "Editor.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetStringLibrary.h"

// Sets default values
AMarkovChain::AMarkovChain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMarkovChain::BeginPlay()
{
	Super::BeginPlay();
	FString txt = "This rainbow has a unicorn flying overhead";
	TArray<FString> NGrams;
	//get trigram
	for(int i =0; i < txt.Len(); i++)
	{
		auto gram = UKismetStringLibrary::GetSubstring(txt,i,i+3);
		NGrams.Add(gram);
	}
	
}

// Called every frame
void AMarkovChain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

