// Fill out your copyright notice in the Description page of Project Settings.


#include "LSystem.h"

// Sets default values
ALSystem::ALSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


FString ALSystem::Generate(int32 NumberOfGenerations)
{
	FString NextSentence("");
	//look at the sentence, if the Axiom key has that letter, replace with its new value
	for(int32 k = 0; k < NumberOfGenerations; k++)
	{
		for(int32 i = 0; i < Sentence.Len(); i++)
		{
			//get the letter at the index of i from our sentence
			FString Current = Sentence.Mid(i,1);

			//if the axiom has the current letter in it
			if(Axiom.Find(Current))
			{
				//next sentence gets the axioms value at the current letter key
				NextSentence += Axiom[Current];
			}
			else
			{	//These are for persistent values
				NextSentence += Current;

			}
		}
	}
	return  NextSentence;
	
}


void ALSystem::Turtle()
{
	FVector PreviousLocation = FVector::ZeroVector;
	FVector NextLocation = FVector::ZeroVector;
	
	for(int32 i = 0; i < Sentence.Len(); i++)
	{
		FString Current = Sentence.Mid(i,1);

		if(Current == "A")
		{
			//TODO: figure out a better way to do this....
		}
		if(Current == "B")
		{
			//DO B Stuff
		}

	}
}


void ALSystem::PotentalStreetGenerator()
{
	//Generate City Bounds
	//Generate Roads
	//Generate cityBlocks
	//Generate Buildings per city block
	//generate building facade
	//generate rooms and corridoors
	//generate furninture placement
/*
	UObject* tempValue;
	EObjectFlags Flags;
	FCreateTexture2DParameters Params;
	TArray<FColor> Colors;
	for(int32 i = 0; i > 512; i++)
	{
		auto tempR = Colors[i].R;
		Colors[i].B = 255;
		
	}
	FImageUtils::CreateTexture2D(512,512,Colors,tempValue,FString(TEXT("herpyDerpy")),Flags,Params);
	*/
}

