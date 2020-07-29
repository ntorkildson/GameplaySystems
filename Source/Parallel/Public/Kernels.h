// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kernels.generated.h"


template <typename K>
K PoissonDisc()
{
	
}



template <typename K>
K GetNeighborsIndex2D(K CurrentCell, K &Neighbors, K GridWidth, K GridDepth)
{

	//TODO: CHeck for out of bounds on these;
	auto N = CurrentCell - GridWidth;
	auto NE = CurrentCell - GridWidth + 1;
	auto E = CurrentCell + 1;
	auto SE = CurrentCell + GridWidth + 1;
	auto S = CurrentCell + GridWidth;
	auto SW = CurrentCell + GridWidth -1;
	auto W = CurrentCell - 1;
	auto NW = CurrentCell - GridWidth - 1;

	Neighbors[N, NE, E, SE, S, SW, W, NW];
	return Neighbors;
};

//Returns 4 cardinal direction neighbors. Does not wrap and is total shit should delete soon
template <typename K>
K FastGetNeighbors2D(K CurrentCell,  K GridWidth,TArray<int32> &NeighborsIndex) // a fast 6 connected kernel(or 4 if you are a 2D image)
{
	
	auto North =  FMath::Max(CurrentCell - GridWidth,0);
	
	auto East =  CurrentCell +1;
	auto South =  CurrentCell + GridWidth;
	auto West = CurrentCell - 1;

	
	NeighborsIndex.AddUnique(North);
	NeighborsIndex.AddUnique(East);
	NeighborsIndex.AddUnique(South);
	NeighborsIndex.AddUnique(West);

	return NeighborsIndex;
}


//Returns the 6 closest neighbors to the current cell and wraps around the grid 
template <typename K>
K FastGetNeighborsWrap(K CurrentCell, K GridDepth, K GridSize, K GridWidth) // a fast 6 connected kernel(or 4 if you are a 2D image)
{
	auto Top = (CurrentCell - GridDepth < 0) ? GridSize - abs(CurrentCell - GridDepth) : CurrentCell - (GridWidth* GridDepth);
        
	auto MidNorth = (CurrentCell - GridWidth < 0) ?   GridSize - abs(CurrentCell - GridWidth) : CurrentCell - GridWidth;
	//east logic

	auto MidEast = (CurrentCell%GridWidth == GridWidth -1) ? floor((CurrentCell /GridWidth) * GridWidth) : CurrentCell + 1;

	auto MidSouth = (CurrentCell + GridWidth > GridSize) ? GridWidth - (GridSize - CurrentCell) : CurrentCell + GridWidth;
	auto MidWest = CurrentCell % GridWidth == 0  ? CurrentCell + (GridWidth -1) : CurrentCell - 1;

	auto Bottom = (CurrentCell + GridDepth > GridSize) ? GridDepth - (GridSize - CurrentCell) : CurrentCell + (GridWidth *GridDepth);

	return neighborList;
}


//TODO: finish implementation
template <typename K>
K VonNeumann2D(K &Grid, int32 StartingIndex, int32 Distance, K GridWidth, K GridHeight, K GridDepth)
{
	auto GridSize = GridWidth * GridHeight * GridDepth;
	TArray<int32> NeighborsIndex;
	
	
	return 1 + (2 * Distance)*(Distance + 1);
	
}


UCLASS()
class PARALLEL_API AKernels : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKernels();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
