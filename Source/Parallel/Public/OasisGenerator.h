// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OasisGenerator.generated.h"

UCLASS()
class PARALLEL_API AOasisGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOasisGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable,Category="Possion Disc")
	TArray<FVector> Draw();
	
	void Setup();
	
	int32 r = 4;
	int32 k = 30;
	TArray<FVector> grid;
	float w = r / FMath::Sqrt(2);
	TArray<FVector>  active;
	int32 cols, rows;
	TArray<FVector>  ordered;
	
	
	//Index and position
	UPROPERTY(EditAnywhere,Category="PoissonSample")
	TMap<int32, FVector> PoissonGrid;
	
	
	//TODO: create debug draw system
	/*Generates a grid based on xSize and YSize */
	UFUNCTION(BlueprintCallable,Category = "PoissonDisc")
    TArray<FVector> GenerateGrid(int32 xDimension, int32 yDimension);

	//Get random indoex from backroundGRid and insert it into the active list
	/*Returns an random index within the x and y bounds of a grid, returns a Random value between 0-randX*randY
	**/
	
	UFUNCTION(BlueprintCallable,BlueprintPure,Category = "PoissonDisc")
    int32 GetRandomIndex(int32 maxX, int32 maxY);
	
	void InsertVectorIntoArray(TArray<FVector> &TargetArray, FVector ItemToAdd, int32 Index);
	
	//while ActiveList.Num() > 1 && ActiveList has a valid index
	
	UFUNCTION(BlueprintCallable,BlueprintPure,Category = "PoissonDisc")
	int32 GetRandomIndexFromArray(int32 ArrayLength);

	//Make a new candidate within the spherical annulus of our random starting index
	UFUNCTION(BlueprintCallable,Category = "PoissonDisc")
    FVector GenerateSphericalAnnulus(FVector SpawnPosition, float InnerRadius, float OuterRadius, bool bShowDebug);

	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "PoissonDisc")
	bool bDistanceCheck(FVector StartPosition, FVector PossibleSpawnLocation, bool bShowDebug = false);
	
	
	//if bIsToFarAway(parent/candidate)
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "PoissonDisc")
	bool bIsToFarAway(FVector CurrentPosition);

	
	/*Select an initial randomly chosen location from within the grid position
	* insert it innto  a new 'active list' array with the random FVector @ index zero
	* returns the random vector within the extents of our cell, cell size is determined by PointRadius 
	 */
	UFUNCTION(BlueprintCallable,Category = "PoissonDisc")
    FVector InitializeRandomPoint(TArray<FVector> OurBackgroundGrid, int32 OurRandomIndex, float OurPointRadius , bool bShowDebugBox);

	/*Get the index of an array. Can use Rand, Rand, xSize to generate a random index*/ 
	UFUNCTION(BlueprintCallable,Category = "PoissonDisc")
	int32 GetArrayIndex(int32 Column, int32 Row, int32 NumRows);

	/*Gets column and row given an idex and number of rows. XSize && index are required to work*/
	UFUNCTION(BlueprintCallable,Category = "PoissonDisc")
	void GetColumnAndRow(int32& column, int32& row, int32 NumRows, int32 Index);


	UFUNCTION(BlueprintCallable,Category = "PoissonDisc")
	TArray<FVector> PoissonDisc(int32 Width, int32 Height, float Radius, int32 FailoverRate);

	bool bGetNeighbors(FVector ourCurrentVector);

	
	UFUNCTION(BlueprintCallable,Category = "PoissonDisc")
	void MainLoopTest(int32 FailNumber, float RadiusAroundPoint);
	
	/*Main loop:
	 * while active list !0 choose a random index from it activelist[randomint] generate k points chosen uniformly from the spherical annulus
	 * between radius r & 2r around xi.
	 * for each point check if its within distance of other neighbors(taken from the background list)
	 * if its far enough(in the donut of 2r) add it to the active list, once k attempts is found, remove current from active list
	 * 
	 */
	
	void PoissonSample();
	
	
	FVector GetRandomPointInGrid();

		
	UFUNCTION(BlueprintCallable,Category = "PoissonDisc")
	TArray<FVector> ReturnNeighbors(int32 startingIndex);

	
	//Total size of the area we are sampling
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="PoissonDisc")
	int32 xSize;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="PoissonDisc")
	int32 ySize;
	
	//radius of the point we are placing
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="PoissonDisc")
	float PointRaduis =1.0f;
	

	//cell size = radius of the point / sqrt of dimensions(2d/3d/etc.)
	UPROPERTY(BlueprintReadOnly,Category="PoissonDisc")
	float CellSize = PointRaduis / FMath::Sqrt(2);

		
	int32 GridWidth;
	int32 GridHeight;
	
	float RadiusSquared = PointRaduis * 2;

	//number of points we are generating
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="PoissonDisc")
	int32 FailTimes = 30;
	
	//grid that encompases the total size of our distribution
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="PoissonDisc")
	TArray<FVector> BackgroundGrid;

	TArray<int32> AGridForReference;
	
	//holds an active point at a specific index.
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="PoissonDisc")
	TArray<FVector> ActiveList;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="PoissonDisc")
    int32 CurrentStartIndex ;
	

};


