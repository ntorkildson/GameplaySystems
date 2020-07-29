// Fill out your copyright notice in the Description page of Project Settings.


#include "CellularAutomata.h"


#include "GeneratedCodeHelpers.h"

// Sets default values
ACellularAutomata::ACellularAutomata()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACellularAutomata::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ACellularAutomata::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ACellularAutomata::GenerateGrid()
{
	//MakeGridWithLocation(CellularGrid,  GridWidth, GridHeight,GridDepth,CellSize,OffSetLocation);

	ECellStates CellType = ECellStates::Dead;

	//MakeGridWithData(CellularGrid, CellType,GridWidth, GridHeight,GridDepth);  //Genereates a 10x10 2D array of size 1 with no offset(centered at 0,0,0 in the world if we spawn it)
	CellularGrid = MakeGrid<ECellStates>(CellType, GridWidth,GridHeight,GridDepth);
	
}


void ACellularAutomata::SetupStartingStates()
{
	//if(StartingStates)

	//verify we have starting states, our default is all dead with center point alive.
	int32 AliveIndex = CellularGrid.Num() / 2;
	CellularGrid[AliveIndex]=ECellStates::Alive;

	
	//randomly initialize the grid
	for(int32 i = 0; i < CellularGrid.Num(); i++)
	{
			
		uint8 Derp = FMath::Rand();
		ECellStates RandomValue = ECellStates(Derp);
		
		CellularGrid[i] = RandomValue;
		
	}

}


void ACellularAutomata::GetNeighbors()
{
	
}

//TOOD: abstract away some of this into other classes so we can easily adjust paramenters
void ACellularAutomata::RunSimulation()
{
	TArray<ECellStates> NewState = CellularGrid; //Do we need this constantly or can I just create a new grid when we nee dit...
	TArray<int32> StartingLocations;
	TArray<int32> Neighbors; //neighbors index update to reflect this name accuracy
	ECellStates NextState;

	

	for(int32 i = 0; CellularGrid.Num() > i; i++)
	{

		ECellStates	CurrentState = CellularGrid[i];
		
		
		//FastGetNeighbors2D(i, GridWidth, Neighbors);  TODO: Getneighbors doesnt work becuase im a dumb
		//remove dead neighbors from the list
		for(int32 j =0; j < Neighbors.Num(); j++)
		{
			if(CellularGrid[Neighbors[j]] == ECellStates::Dead)
			{
				Neighbors.Remove(j);
			}

		}
		
		//Curernt Rules to live or die by
		//any dead cell with 3 live neighbors becomes alive
		if(CurrentState == ECellStates::Dead && Neighbors.Num() == 3) 
		{
			NextState = ECellStates::Alive;
		}
		//any live cell with 2 or 3 live neighbors becomes alive
		if(CurrentState == ECellStates::Alive && (Neighbors.Num() > 1 && Neighbors.Num() < 4))
		{
			NextState = ECellStates::Alive;
		}
		else//everything else is dead
		{
			NextState = ECellStates::Dead;
		}

		NewState[i] = NextState;
		
	}
	
	//our main Grid is the new state, we empty our new state and do it all over again

	//Update our simulation with whatever we want it to actually do....
	
	CellularGrid = NewState;
	NewState.Empty();

	DrawData();
	
}

void ACellularAutomata::DrawData()
{
	for(auto &i : CellularGrid)
	{
		//Do Something with the data like:
		/*
		FTransform SpawnLocation;
		SpawnLocation = FVector(GridInex * GridOffset * Width);
		const FActorSpawnParameters NewParams;
		GetWorld()->SpawnActor(SpawnLocation,NewParams);
		now we have however many actos spawned where the grid should be.
		this is probably updating every frame if its an actor.
		*/
	}
}


void ACellularAutomata::SetupGrid()
{

	//Generate our reference grid
	GenerateGrid();

	//Setup our starting states
	SetupStartingStates();

	RunSimulation();
	
}

