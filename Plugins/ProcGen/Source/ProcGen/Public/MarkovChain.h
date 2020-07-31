// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MarkovChain.generated.h"

//NGRAM = selection of 'states' on a given input system(string or whatever)

//MarkovCHain-> State/Action Pair system



UCLASS()
class PROCGEN_API AMarkovChain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMarkovChain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
