// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"

#include "GameFramework/Actor.h"
#include "TreeGenerator.generated.h"

USTRUCT() struct FMyInterpStruct
{
	GENERATED_BODY()

UPROPERTY() float Brightness;

	UPROPERTY() float BrightnessGoal; //interping to

	UPROPERTY() FVector Location;

	UPROPERTY() FVector LocationGoal;

	UPROPERTY() float Alpha;

	void InterpInternal()
	{
		Location = FMath::Lerp(Location,LocationGoal,Alpha); Brightness = FMath::Lerp(Brightness,BrightnessGoal,Alpha);

		//Brightness out is returned, FVector is returned by reference float Interp(const float& NewAlpha, FVector& Out) { //value received from rest of your game engine Alpha = NewAlpha;

		//Internal data structure management InterpInternal();

		//Return Values Out = Location; return Brightness; } FMyInterpStruct() { Brightness = 2; BrightnessGoal = 100;
		Alpha = 0;

		Location = FVector::ZeroVector;
		LocationGoal = FVector(0,0,200000);
	}
};


//Branch node is simply a 2 point link
USTRUCT(BlueprintType)
struct FBranchNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Branch")
	FVector StartLocation;


	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Branch")
	FVector EndLocation;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Branch")
	int32 Length;

	UPROPERTY(EditAnywhere, Category = YourCategory)
    class USplineComponent* Spline;

	FBranchNode(FVector x_, FVector y_) : StartLocation(x_), EndLocation(y_)
	{
	}
	FBranchNode() : StartLocation(0), EndLocation(0){}
		
};


UCLASS()
class PARALLEL_API ATreeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreeGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*Generates a Z up group of points*/
	UFUNCTION(BlueprintCallable, Category = "Tree | Generator")
	TArray<FVector> GenerateTrunkPoints();	
	
	/*Generates some horizontal points*/
	UFUNCTION(BlueprintCallable,Category="Tree | Generator")
	TArray<FVector> GenerateBranchPoints(FVector StartLocation, FVector EndLocation, int32 NumberOfBranches, bool bTraceToGround);

	TArray<FVector> GenerateRootPoints();

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Tree | Generator")
	FBranchNode	StartingBranchLength;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Tree | Generator")
	float TreeHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Tree | Generator")
    float RootLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Tree | Generator")
    float RandomVerticalSlide;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Tree | Generator")
    float BranchStartingHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Tree | Generator")
	int32 NumberOfVerticalBranches;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Tree | Generator")
    int32 NumberOfRoot;

	
	UFUNCTION(BlueprintNativeEvent,CallInEditor, BlueprintCallable,Category = "Tree Generator")
	void GenerateATree();

	
	UFUNCTION(BlueprintCallable, Category = "Tree | Generator")
	void FractalTreeRecursive(TArray<FVector> &Reference, FVector StartLocation, FRotator RotationAmount, int32 Length, int32 StepCount);
	
	//DiffuseLimitedAggregation
	
	//CellularAutamata
		//Some Rules for it
	
	//Erosion algorithm(s)
	
	//boids

	//Lsystems
	
	//WaveFunctionCollapse

	//markovChain
	//n-grams(arbitrary nubmeres?)
	//voronoi and other noise functions
	
	//split grammers
	
	
};

