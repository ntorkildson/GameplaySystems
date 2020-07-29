// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GridHelper.h"


#include "GameFramework/Actor.h"
#include "CellularAutomata.generated.h"


/*
 * Ceullular automata requires a set of rules for each grid state
 * alive/dead/etc...
 */

UENUM(BlueprintType)
enum class ECellStates : uint8
{
	Alive,	
	Dead,
	
};

USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY()

public:
	ECellStates CellState;
	FVector MyLocation;
	
};

	

UCLASS()
class PROCGEN_API ACellularAutomata : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellularAutomata();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere,Category ="Cellular Automata | Initial Variables")
	TArray<ECellStates> CellularGrid;
	
		
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category ="Cellular Automata | Initial Variables")
	int32 GridWidth=10;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category ="Cellular Automata | Initial Variables")
	int32 GridHeight=10;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category ="Cellular Automata | Initial Variables")
	int32 GridDepth=0;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category ="Cellular Automata | Initial Variables")
	int32 CellSize = 10;
	//Defaults to the actors location in the world
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category ="Cellular Automata | Initial Variables")
	FVector OffSetLocation = GetActorLocation();

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category ="Cellular Automata | Initial Variables")
	int32 NumberOfIterations;

				
	//Should probably return the grid we want to use.
	UFUNCTION(BlueprintCallable,Category ="Cellular Automata | Generation")
	void GenerateGrid();

	//Calls GenerateGrid, SetupStartingStates and RunSimulation;
	UFUNCTION(BlueprintCallable,Category ="Cellular Automata | Generation")
	void SetupGrid();

	//the initial states for our grid to use
	UFUNCTION(BlueprintCallable,Category ="Cellular Automata | Generation")
	void SetupStartingStates();

	//TODO: Should allow us to easily select what Getneighbors class we want to use
	UFUNCTION(BlueprintCallable,Category ="Cellular Automata | Generation")
	void GetNeighbors();
	
	
	UFUNCTION(BlueprintCallable,Category ="Cellular Automata | Generation")
	virtual void RunSimulation();

	void DrawData();
	
};




class CARules
{
	
};

class ConwayGOL : public CARules
{
	//idk how to do this yet...
	ECellStates currentRules;

	
	/*
	switch(currentRules)
	{
		if(OurState == Alive)
		{
			if(GetNeighbors().Num > 1 && < 4)
				NewState = ECellStates::Alive:
		}
		if(OurState == Dead)
		{
			if(GetNeighbors().Num == 3)
				NewState == Dead;
		}
		else NewState == Dead;
	}
	*/
	
};

