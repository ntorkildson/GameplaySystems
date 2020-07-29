// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GridHelper.generated.h"

/**
 * Helper function for creating 1D up to 3D grids, templated so programmers dont have to contunually recreate the same for loops for different data types
 */


/*Returns a grid of type GridData*/
template <typename GH> 
TArray<GH> MakeGrid( GH GridData, int GridWidth, int GridHeight, int GridDepth)
{

	TArray<GH> NewGrid; //New Grid
	for (int i = 0; GridWidth >= i; i++)
	{
		for (int j = 0; GridHeight >= j; j++)
		{
			for (int k = 0; GridDepth >= k; k++)
			{
				NewGrid.Add(GridData);
			}
		}
	}
	return NewGrid;
	
}


/*
 returns a 1D array of size Height*Widgth*Depth with Locations being set by (Location * Cellsize + OffSetLocation)
NewGrid is the array type we are passing
DataType is relevant if we are NOT  using it in 3d space
CellSize is relevant if we are using it in 3d space
offset location is relevant if the grid has a relative location in 3d space
*/

template<typename GH>
   GH MakeGridWithLocation(TArray<GH> &NewGrid, int32 GridWidth, int32 GridHeight, int32 GridDepth, int32 CellSize, FVector OffsetLocation)
{
	
	for (int i = 0; GridWidth > i; i++)
	{
		for (int j = 0; GridHeight > j; j++)
		{
			for (int k = 0; GridDepth > k; k++)
			{
				/*
				 * if(CellSize > 0
				 * location based, otherwise its probably just data
				 */
				GH Temp(i * CellSize + OffsetLocation.X, j * CellSize + OffsetLocation.Y, k * CellSize + OffsetLocation.Z);
				NewGrid.AddUnique(Temp);
			}
		}
	}
	return OffsetLocation; //This is just worthless...
	
}



//returns the index from an array given an x,y,z location
template <typename GH>
GH GetGridIndexFromLocation(GH xLocation, GH yLocation, GH zLocation, GH GridWidth, GH GridHeight)
{
	//Locations start at 0,0,0
	//a 3x3x3 Grid center point would be 1,1,1 and the max extent would be 2,2,2
	return xLocation + GridWidth * yLocation + GridWidth * GridHeight * zLocation;
}

//Returns an FVector coordinate from an index and a grid
template <typename GH>
GH GetLocationFromGridIndex(GH Index, GH Width, GH Height)
{

	FVector Location;
	Location.X = Index % Width;
	Location.Y = (Index / Width) % Height;
	Location.Z  = Index / (Width * Height);
	return Location;
}


//sets index of the grid with newData
template <typename GH>
GH SetDataAtIndex(int Index, GH &NewData, GH &Grid)
{
	return Grid[Index] = NewData;
}

template <typename GH>
GH GetDataAtIndex(int Index, GH &Grid)
{
	return Grid[Index];
}



UCLASS()
class PROCGEN_API UGridHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	public:

	UFUNCTION(BlueprintCallable, Category ="ProcGenLibrary | GridHelper")
	void GenerateGrid();

//	FVector GetLocationFromIndex(int32 Index, int32 GridWidth, int32 GridHeight);
	
	
};
