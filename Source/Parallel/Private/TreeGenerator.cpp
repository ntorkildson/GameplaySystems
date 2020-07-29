// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeGenerator.h"

#include "DrawDebugHelpers.h"



struct FPaintContext;
// Sets default values
ATreeGenerator::ATreeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}



// Called when the game starts or when spawned
void ATreeGenerator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATreeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<FVector> ATreeGenerator::GenerateTrunkPoints()
{
	TArray<FVector>OurPoints;

	//Generate Starting Spawn point(0,0,0)
	FVector StartingLocation = GetActorLocation();

	//Generate inital spawning point
	OurPoints.Add(StartingLocation);

	//for each of the branches generate a point
	for(int32 i = 1; i < NumberOfVerticalBranches + 1; i++)
	{
		float NewXValue = FMath::RandRange(StartingLocation.X - RandomVerticalSlide, StartingLocation.X + RandomVerticalSlide);
		float NewYValue = FMath::RandRange(StartingLocation.Y - RandomVerticalSlide, StartingLocation.Y + RandomVerticalSlide);
		float NewZValue = ((TreeHeight - 10 - BranchStartingHeight) / (NumberOfVerticalBranches)) * i + BranchStartingHeight + StartingLocation.Z;
		FVector finalTemp(NewXValue, NewYValue,NewZValue);
		OurPoints.Add(finalTemp);
	}

			
	return OurPoints;
}

TArray<FVector> ATreeGenerator::GenerateBranchPoints(FVector StartLocation, FVector EndLocation, int32 NumberOfBranches, bool bTraceToGround)
{
	TArray<FVector>OurPoints;

	//Generate inital spawning point
	OurPoints.Add(	StartLocation);
	
	FVector LocalStart = EndLocation;
	
	
	//Trace variables if necessary
	FHitResult OutHit;
	FCollisionObjectQueryParams Params;
	

	
	//for each of the Roots, generate a point
	for(int32 i = 1; i <= NumberOfBranches ; i++)
	{
		//Step the Local Start location outward i units * distance of the spline / numberOfBranchPoints;
		//Trace is ForwardVector(randomRotation.Vec()) * Distance we are traveling + startLocation
		//start location will update every time i does to be equal to the previous end location
		//
		FRotator TempRotationDirection;// = UKismetMathLibrary::RandomRotator(false);
		TempRotationDirection.Pitch = 0;
		TempRotationDirection.Yaw = FMath::FRand() * 360;
		FVector TempDirection = TempRotationDirection.Vector();
		TempDirection *=RootLength * i;
		
		
		FVector NewEndLocation = LocalStart + TempDirection;
		if(bTraceToGround)
		{
			NewEndLocation; // TraceStart
			FVector TraceEnd = FVector(NewEndLocation.X, NewEndLocation.Y, NewEndLocation.Z -500);
			GetWorld()->LineTraceSingleByObjectType(OutHit,NewEndLocation,TraceEnd,Params);
			if(OutHit.bBlockingHit)
			{
				NewEndLocation.Z= OutHit.Location.Z;
			}
		
		}
		OurPoints.Add(NewEndLocation);
		LocalStart = NewEndLocation;
		
		/*
		
		float Distance = i * RootLength;
		
		float NewXValue = Distance + LocalStart.X;
		float NewYValue = 0;//FMath::RandRange(LocalEnd.Y - RandomVerticalSlide, LocalEnd.Y + RandomVerticalSlide);
		float NewZValue = 0;
			
		
		if(bTraceToGround == true)
		{		
		//StartTrace = StartLocation;
		//EndTrace = FVector(StartTrace.X, StartTrace.Y, StartingLocation.Z - 500);
		//trace each point towards the ground and update its position.
		//GetWorld()->LineTraceSingleByObjectType(OutHit, StartTrace, EndTrace,  Params);
		//if(OutHit.bBlockingHit)
		//{
		//	 NewZValue = OutHit.Location.Z;
		//	FVector finalTemp(NewXValue, NewYValue, NewZValue);
		//	OurPoints.Add(finalTemp);
		//}
			
			
		}
		
		else	
		{
		NewZValue = StartLocation.Z;		
		FVector finalTemp(NewXValue, NewYValue, NewZValue);
		LocalStart = finalTemp;
		OurPoints.Add(finalTemp);
		}

		}	

	
		*/
	}	
	return OurPoints;
}

TArray<FVector> ATreeGenerator::GenerateRootPoints()
{

	TArray<FVector> OurPoints;
	//Generate starting point (base of tree)

	//for numberOfRoots
	//Get a random direction from starting location
	//trace forward 'x' units to see if ground goes upwards
	//if it doesnt, trace downards from end point and add the hit point to the generated points.
	//Do this part N times
	
	
	return OurPoints;
}


void ATreeGenerator::FractalTreeRecursive(TArray<FVector> &Reference,FVector StartLocation, FRotator RotationAmount, int32 Length, int32 StepCount)
{
	float EndZLocation = StartLocation.Z + Length;
	
	FVector EndLocation = FVector(StartLocation.X, StartLocation.Y, EndZLocation);
	//rotate end location 
	EndLocation =  EndLocation.RotateAngleAxis(RotationAmount.Yaw,StartLocation);
	if(StepCount > 0)
	{
		
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation,FColor::Red,false,1.0f,0,3);
		//Add to array here.

		StartLocation = EndLocation;
		Length = Length * 0.7;
		Reference.Emplace(EndLocation);
		FractalTreeRecursive(Reference, EndLocation,RotationAmount, Length*0.7f,StepCount -1);

		
		FractalTreeRecursive(Reference, EndLocation, RotationAmount *-1.0f, Length*0.7,StepCount -1);
	
		
	}
	
}


void ATreeGenerator::GenerateATree_Implementation()
{
	//Currently this is all in blueprints
	
}



//ProcGen Library
/*
 * cellular automata
 * FractalTrees
 * 	-recursive and OOP
 * L-system
 * space colonization
 * Diffuse limited aggregation
 * some noise generators
 * 
 */

