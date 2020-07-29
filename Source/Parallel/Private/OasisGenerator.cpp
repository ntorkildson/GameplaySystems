// Fill out your copyright notice in the Description page of Project Settings.


#include "OasisGenerator.h"
#include "DrawDebugHelpers.h"
#include "TreeGenerator.h"

#include "Engine/Engine.h"


// Sets default values
AOasisGenerator::AOasisGenerator()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOasisGenerator::BeginPlay()
{
    Super::BeginPlay();
}



void AOasisGenerator::Setup()
{
    auto width = xSize;
    auto height = ySize;
    // STEP 0
    cols = floor(width / w);
    rows = floor(height / w);
    for (auto i = 0; i < cols * rows; i++)
    {
        grid[i] = FVector(-1,-1,-1);
        PoissonGrid.Add(i,FVector(-1,-1,-1));
    }

    
    // STEP 1
    auto x = width / 2;
    auto y = height / 2;
    auto i = floor(x / w);
    auto j = floor(y / w);
    auto pos = FVector(x, y, 0);
    grid[i + j * cols] = pos;
    PoissonGrid[i+j*cols] = pos; 
    active.Emplace(pos);
}


TArray<FVector> AOasisGenerator::Draw()
{
    Setup();
    for (auto total = 0; total < 25; total++)
    {
        if (active.Num() > 0)
        {
            auto randIndex = FMath::FloorToInt(FMath::RandRange(0,active.Num()));
            auto pos = active[randIndex];
            auto found = false;
            for (auto n = 0; n < k; n++)
            {

                float angle = FMath::Rand() * 3.14 * 2;
                FVector dir(FMath::Sin(angle), FMath::Cos(angle),0.0f);
                FVector sample = pos + dir * FMath::RandRange(r, 2*r);

                /*althernative version*/
               // auto sample = FVector(FMath::Rand(), FMath::Rand(), FMath::Rand());
                //auto m = FMath::RandRange(r, 2 * r);
               //// sample.operator*=(m);
               // sample.add(pos);

                /*end version differences*/
                auto col = floor(sample.X / w);
                auto row = floor(sample.Y / w);

                if (
                    col > -1 &&
                    row > -1 &&
                    col < cols &&
                    row < rows &&
                    !grid.IsValidIndex(col+row*cols)
                )
                {
                    auto ok = true;
                    for (auto i = -1; i <= 1; i++)
                    {
                        for (auto j = -1; j <= 1; j++)
                        {
                            auto index = col + i + (row + j) * cols;
                            auto neighbor = grid[index];
                            if (grid.IsValidIndex(index))
                            {
                                FVector dist;
                                auto d = dist.Distance(sample, neighbor);
                                if (d < r)
                                {
                                    ok = false;
                                }
                            }
                        }
                    }
                    if (ok)
                    {
                        found = true;
                        grid[col + row * cols] = sample;
                        active.Emplace(sample);
                        ordered.Emplace(sample);
                        // Should we break?
                        break;
                    }
                }
            }

            if (!found)
            {
                active.RemoveAt(randIndex, 1);
            }
        }
    }
    
    for (auto i = 0; i < ordered.Num(); i++)
    {
        if(ordered.IsValidIndex(i))//if (ordered[i])
        {
            
            //Draw stuff here
            //stroke(i % 360, 100, 100);
            //strokeWeight(r * 0.5);
            //point(ordered[i].x, ordered[i].y);
        }
    }
    return ordered;
    // for (var i = 0; i < active.length; i++) {
    //   stroke(255, 0, 255);
    //   strokeWeight(1);
    //   point(active[i].x, active[i].y);
    // }
    //console.log(active.length);
}




TArray<FVector> AOasisGenerator::GenerateGrid(int32 xDimension, int32 yDimension)
{
    //clears the array if its already got data in it
    if (BackgroundGrid.Num() > 0)
        BackgroundGrid.Empty();
    //Step 0 : initialization
    for (int32 i = 0; xDimension > i; i++)
    {
        for (int32 j = 0; yDimension > j; j++)
        {
            FVector temp(i * CellSize + GetActorLocation().X, j * CellSize + GetActorLocation().Y,
                         GetActorLocation().Z);
            BackgroundGrid.AddUnique(temp);
        }
    }
    return BackgroundGrid;
}

int32 AOasisGenerator::GetRandomIndex(int32 maxX = 1, int32 maxY = 1)
{
    int32 randX = FMath::RandRange(0, maxX);
    int32 randY = FMath::RandRange(0, maxY);
    //return randX * randY;
    int32 ourIndex = 0;
    return FMath::Clamp(ourIndex, 0, (randX * randY) - 1);

    //the GridWidth(Width/cellSize) multiplied by the (height/2) / CellSize + (width / 2) / CellSize;
}

int32 AOasisGenerator::GetRandomIndexFromArray(int32 ArrayLength)
{
    //returns the max value between 0 and arrayLengh-1 so we dont have any stupid negative numbers
    return FMath::Max(0, FMath::RandRange(0, ArrayLength - 1));
}


FVector AOasisGenerator::InitializeRandomPoint(TArray<FVector> OurBackgroundGrid, int32 OurRandomIndex,
                                               float OurPointRadius, bool bShowDebugBox = false)
{
    //get the starting location of our point

    FVector OurStartLocationVector = OurBackgroundGrid[OurRandomIndex];
    //generate a cube
    FVector BoxExtent(OurPointRadius, OurPointRadius, OurPointRadius);
    FVector BoxCenter = (OurStartLocationVector + BoxExtent) / 2;

    //shows the extent of this box space
    if (bShowDebugBox)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, TEXT("should shwo debug box"));
        ::DrawDebugBox(GetWorld(), BoxCenter, BoxExtent, FColor::Black, true, -1, SDPG_World, 1.0f);
    }

    //generate a random point inside the box
    FVector RandomStartSpawn = FMath::RandPointInBox(FBox(OurStartLocationVector, OurStartLocationVector + BoxExtent));

    //return the final point	
    return RandomStartSpawn;
}


//TODO:Fix this
FVector AOasisGenerator::GenerateSphericalAnnulus(FVector OurSpawnPosition, float InnerRadius, float OuterRadius, bool bShowDebug)
{
/*
    //Smart guy fix version
    int32 seed = FMath::Rand();
    float epsilon = 0.0001f;
    
    auto angle = 2 * 3.14 * (seed + 1.0f * 1 / FailTimes);
    auto NewRadius = InnerRadius + epsilon;
    FVector OurNewSpawnTest;
    
    OurNewSpawnTest.X = OurSpawnPosition.X + NewRadius * FMath::Cos(angle);
    OurNewSpawnTest.Y = OurSpawnPosition.Y + NewRadius * FMath::Sin(angle);
    OurNewSpawnTest.Z = GetActorLocation().Z;
    return OurNewSpawnTest;
    */
    
  
    //angle to select from
    //magnitude is the distance from the start location
    //direction is the direction we are going
    //return the end location of what is basically a trace
    
    
    float angle = FMath::Rand() * 3.14 * 2;
    FVector dir(FMath::Sin(angle), FMath::Cos(angle),0.0f);
    FVector OurNewSpawnTest = OurSpawnPosition + dir * FMath::RandRange(InnerRadius, OuterRadius);

    /*         
    // auto sample = FVector(FMath::Rand(), FMath::Rand(), FMath::Rand());
    //auto m = FMath::RandRange(r, 2 * r);
    //// sample.operator*=(m);
    // sample.add(pos);

 */

    if(bShowDebug)
    {
        ::DrawDebugSphere(GetWorld(), OurNewSpawnTest, InnerRadius, 12, FColor::Black, false, 12, SDPG_World, 5.0);
        ::DrawDebugSphere(GetWorld(), OurNewSpawnTest, OuterRadius, 12, FColor::Yellow, false, 12, SDPG_World, 0.2f);

    }
    return OurNewSpawnTest;

    
}

bool AOasisGenerator::bDistanceCheck(FVector StartPosition, FVector PossibleSpawnLocation, bool bShowDebug)
{
      //if the current x/y positions are greater than zero and less than the size of the total grid
    if (0 <= PossibleSpawnLocation.X && PossibleSpawnLocation.X < xSize && 0 <= PossibleSpawnLocation.Y && PossibleSpawnLocation.Y < ySize)
    {
        int32 CellX = PossibleSpawnLocation.X / CellSize;
        int32 CellY = PossibleSpawnLocation.Y / CellSize;
    
        int32 searchStartX = FMath::Max(CellX - 2, 0);
        int32 SearchStartY = FMath::Max(CellY - 2, 0);

        int32 SearchEndX = FMath::Min(CellX + 3, GridWidth);
        int32 SearchEndY = FMath::Min(CellY + 3, GridHeight);

        //check neighbors within a range around the start point
        for (int32 x = searchStartX; x <= SearchEndX; x++)
        {
            for (int32 y = SearchStartY; y <= SearchEndY; y++)
            {
                //is current index we are searching valid within the background grid
                if (BackgroundGrid.IsValidIndex((x * GridWidth) + y))
                {
                    if(bShowDebug)
                    {
                        FVector Extent(CellSize,CellSize,CellSize);
                        ::DrawDebugBox(GetWorld(),  BackgroundGrid[y + GridWidth * x], Extent, FColor::Blue , false, 2.0, SDPG_World, 15.0);

                    }
                    FVector tempDist;
                    float sqrDist = tempDist.DistSquared(PossibleSpawnLocation, BackgroundGrid[y + GridWidth * x]);
                    
                    //Row + Column * NumRows;
                    BackgroundGrid[x * GridWidth + y];
                    UE_LOG(LogTemp, Display, TEXT("%f < %f"), sqrDist, RadiusSquared);

                    if (sqrDist < RadiusSquared)
                    {
                        return false;
                    }
                    /*
                    float dx = CurrentPosition.X;
                    float dy = CurrentPosition.Y;
                    if(dx * dx + dy * dy < RadiusSquared)
                    {
                        return false;
                    }
                    */
                }
            }
        }
        return true;
    }
    return false;
}


int32 AOasisGenerator::GetArrayIndex(int32 Column, int32 Row, int32 NumRows)
{
    return Row + Column * NumRows;
}

void AOasisGenerator::GetColumnAndRow(int32& column, int32& row, int32 NumRows, int32 Index)
{
    column = Index % NumRows;
    row = Index / NumRows;
}

TArray<FVector> AOasisGenerator::PoissonDisc(int32 Width, int32 Height, float Radius, int32 FailoverRate)
{
    bool bWasAccepted = false;
    RadiusSquared = Radius * 2;
    CellSize = FMath::CeilToInt(PointRaduis / sqrt(2));
    GridWidth = FMath::CeilToInt(Width / FMath::Max(1.0f, CellSize));
    GridHeight = FMath::CeilToInt(Height / FMath::Max(1.0f, CellSize));
    TArray<FVector> SpawnPoints;
    //Generate Grid
    BackgroundGrid = GenerateGrid(GridWidth, GridHeight);

    //return value holds all the spawnable locations;
    TArray<FVector> FinalPoints;
    
    //Pick the first sample
    /*The other version
     *FVector StartingVector = sample(xSize / 2,ySize / 2,GridWidth,BackgroundGrid,ActiveList);
     */
    //Get a random starting cell from within our grid to start at
    int32 ourRandomIndex = GetRandomIndexFromArray(BackgroundGrid.Num());
    if (!BackgroundGrid.IsValidIndex(ourRandomIndex))
    {
        UE_LOG(LogTemp, Error, TEXT("backgroundGrid has an invalid index"));
    }
    
    FVector StartingVector = BackgroundGrid[ourRandomIndex];
    //Add that starting lcoation to our ActiveList
    ActiveList.Emplace(StartingVector);
    while (ActiveList.Num() > 1)
    {
        // Pick a random existing sample from the ActiveList.

        //generate a random index
        //auto i = FMath::Rand() * ActiveList.Num();
        ourRandomIndex = GetRandomIndexFromArray(ActiveList.Num());

        if (!ActiveList.IsValidIndex(ourRandomIndex))
        {
            UE_LOG(LogTemp, Error,
                   TEXT("Active List has an invalid index, ourRandomIndex is: %d and our array size is: %d"),
                   ourRandomIndex, ActiveList.Num()-1);
            break;
        }
        

        FVector parent = ActiveList[ourRandomIndex];
        int32 seed = FMath::Rand();
        float epsilon = 0.0001f;

        
        //make a new candidate
        for (int32 j = 0; j < FailoverRate; j++)
        {
            //Generate SphericalAnnulus
            auto a = 2 * 3.14 * (seed + 1.0f * j / FailoverRate);
            auto rad = Radius + epsilon;
            auto x = parent[0] + rad * FMath::Cos(a);
            auto y = parent[1] + rad * FMath::Sin(a);
            
            //accept candidates that are inside the allowed extent
            //and farther than 2*radius to all existing samples
            //if x is greater than 0 and less than the width of the array(XSize)
            //&& y is greater than 0 and less than the height of the array(YSize)
            //and bIsFar(x, y) returns true
            UE_LOG(LogTemp, Display, TEXT("Current Vector is: %s"), *parent.ToString());
            UE_LOG(LogTemp, Display, TEXT("Current activeList is: %s"), *ActiveList[ourRandomIndex].ToString());

            if (bIsToFarAway(parent))
            {
                //generate a new index to sample

                //int32 s = AGridForReference[GridWidth * (FMath::Max(y/CellSize,0.0f)) + (FMath::Max(x/CellSize,0.0f))] = SpawnPoints.Num();
                ActiveList.Emplace(parent);
                FinalPoints.Emplace(parent);
                bWasAccepted = true;
            }
            /*
            if (0 <= x && x < Width && 0 <= y && y < Height && bIsToFarAway(parent))
            {
                
                //sample(x,y);
                int32 tempIndex = GridWidth * (y / CellSize) + (x/CellSize);
                if(BackgroundGrid.IsValidIndex(tempIndex))
                {
                    auto s = BackgroundGrid[tempIndex];
                    ActiveList.Emplace(s);
                }
                break;
            }
            */
        }
        //if none of Failover candidates were accepted, remove it from ActiveList
        //auto r = ActiveList.Pop();
        if (!bWasAccepted)
        {
            if (ActiveList.IsValidIndex(ourRandomIndex))
            {
                UE_LOG(LogTemp, Display,
                       TEXT("No candidates accepted and Failover Reached, removing %d index from ActiveList"),
                       ourRandomIndex);
                ActiveList.RemoveAt(ourRandomIndex);
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT("No candidates accespted but Index: %d,  is invalid"), ourRandomIndex);
            }
        }
    }
    return FinalPoints;
}

//if the possible candidate is within the bounds of the starting activeList vector...

bool AOasisGenerator::bIsToFarAway(FVector CurrentPosition)
{
    //if the current x/y positions are greater than zero and less than the size of the total grid
    if (0 <= CurrentPosition.X && CurrentPosition.X < xSize && 0 <= CurrentPosition.Y && CurrentPosition.Y < ySize)
    {
        int32 CellX = CurrentPosition.X / CellSize;
        int32 CellY = CurrentPosition.Y / CellSize;
    
        int32 searchStartX = FMath::Max(CellX - 2, 0);
        int32 SearchStartY = FMath::Max(CellY - 2, 0);

        int32 SearchEndX = FMath::Min(CellX + 3, GridWidth);
        int32 SearchEndY = FMath::Min(CellY + 3, GridHeight);

        for (int32 x = searchStartX; x <= SearchEndX; x++)
        {
            for (int32 y = SearchStartY; y <= SearchEndY; y++)
            {
                if (BackgroundGrid.IsValidIndex((x * GridWidth) + y))
                {
                    FVector tempDist;
                    float sqrDist = tempDist.DistSquared(CurrentPosition, BackgroundGrid[y + GridWidth * x]);
                    UE_LOG(LogTemp, Display, TEXT("CurrentPosition is: %s"), *CurrentPosition.ToString());

                    UE_LOG(LogTemp, Display, TEXT("BackgroundGrid index is: %d"), GetArrayIndex(GridWidth,y,x));
                    UE_LOG(LogTemp, Display, TEXT("BackgroundGrid vector at index is: %s"),
                           *ActiveList[GetArrayIndex(GridWidth,y,x)].ToString());

                    UE_LOG(LogTemp, Display,
                           TEXT("Distance between our current position and our background location is: %f"), sqrDist);


                    //Row + Column * NumRows;
                    BackgroundGrid[x * GridWidth + y];
                    UE_LOG(LogTemp, Display, TEXT("%f < %f"), sqrDist, RadiusSquared);

                    if (sqrDist < RadiusSquared)
                    {
                        return false;
                    }
                    /*
                    float dx = CurrentPosition.X;
                    float dy = CurrentPosition.Y;
                    if(dx * dx + dy * dy < RadiusSquared)
                    {
                        return false;
                    }
                    */
                }
            }
        }
        return true;
    }
    return false;
}

bool AOasisGenerator::bGetNeighbors(FVector ourCurrentVector)
{
    return true;
}


void AOasisGenerator::MainLoopTest(int32 FailNumber,
                                   float OurPointRadius = 1.0f)
{
    /*
    bool bCandidateAccepted = true;
    bool bIsFound = false;
    //Create our main grid
    GenerateGrid(xSize,ySize);
        
    //get a random starting cell from within our grid
    int32 ourRandomIndex =0;
    FMath::Clamp(ourRandomIndex,0,GetRandomIndex(xSize,ySize));
    
    //add that random grid to our active list @ index 0
    ActiveList.AddUnique(BackgroundGrid[ourRandomIndex]);
        
    //while our active list > 0
    while (ActiveList.Num() > 0)
    {
        //chose a random index from the active list
        UE_LOG(LogTemp,Error,TEXT("ActiveList array size is: %d"), ActiveList.Num())
        int32 NewRandomIndex = FMath::RandRange(0, ActiveList.Num()-1);

        //create a random point within the bounds of our starting cell(create a box and grab a point within it)

                
        //Generate up to K points uniformly between the spherical annulus between radius R ** 2R around Xi 
        for(int32 x = 0; FailNumber > x; ++x)
        {
            //TODO: this should be the background list and not activelist
            //FVector RandomSpawnPosition = InitializeRandomPoint(ActiveList,NewRandomIndex,OurPointRadius,false);
            FVector RandomSpawnPosition = InitializeRandomPoint(BackgroundGrid,NewRandomIndex,OurPointRadius,true);

            //Generate spherical annulus
            FVector CurrentPosition = GenerateSphericalAnnulus(RandomSpawnPosition,OurPointRadius,OurPointRadius*2);	
                    
            //get our current position inside the grid
            int32 CurrentColumn = FMath::TruncToInt( CurrentPosition.X )/ CellSize;
            int32 CurrentRow = FMath::TruncToInt(CurrentPosition.Y )/ CellSize;
            
            //check for neighbors
            for (int32 i = -1; i <= 1; i++)
            {
                for (int32 j = -1; j <=1; j++)
                {
                    //UE_LOG(LogTemp,Error,TEXT("neighbor check should be less than 9 and it is: : %d"), i*j);

                    //if a point is far enough from the existing samples(in our neighbors)
                    //use it as our next point and add it to the active list
                    //if no points have been found after i == Failover, remove i from activeList
                    // get the neighbors position given the indexes
                    
                     int32 currentIndex = GetArrayIndex(CurrentColumn + i, CurrentRow + j, ySize);
                    
                    if(currentIndex > -1 && currentIndex < BackgroundGrid.Num())
                    {
                        FVector neighbors = BackgroundGrid[currentIndex];

                        //check distance between sample and neighbors
                        FVector Distance;
                        float CurrentDistance = Distance.Distance(CurrentPosition,neighbors);
                    
                        //if the point is adequately far from the existing samples, emit as next sample and add to active list.
                        if(CurrentDistance < PointRaduis)
                        {
                            bCandidateAccepted = false;
                            break;
                        }

                    }
                }
                
            }
            if(bCandidateAccepted)
            {
                //UE_LOG(LogTemp,Error,TEXT("Candidate accepted"));

                bIsFound = true;
                UE_LOG(LogTemp,Error,TEXT("BackgroundGrid INdex location = %d "), CurrentColumn + CurrentRow * ySize);
                BackgroundGrid[CurrentColumn + CurrentRow * ySize] = CurrentPosition;
                ActiveList.AddUnique(CurrentPosition);

            }
            else
                ActiveList.RemoveAt(NewRandomIndex);
            
        }
        
        ActiveList.RemoveAt(NewRandomIndex);
        
        int32 testSize = ActiveList.Num();
        
    }
    */
}


TArray<FVector> AOasisGenerator::ReturnNeighbors(int32 startingIndex)
{
    TArray<FVector> tempValue;
    return tempValue;
}


//main loop
void AOasisGenerator::PoissonSample()
{
    //generate a grid of x/y size
    GenerateGrid(xSize, ySize);


    //get a random starting point
    int32 startingPoint = GetRandomIndex(xSize, ySize);


    bool candidateAccepted = true;
    bool found = false;


    //Step 2:
    //while the active list is not empty choose a random index i
    while (ActiveList.Num() > 0)
    {
        //choose a random index from the ActiveList
        int32 randomIndex = FMath::RandRange(0, ActiveList.Num());

        //generate k points between radius r and 2r around xi
        for (int32 x = 0; FailTimes > x; ++x)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed times : %d"), x);
            //for each point, check if its in distance r || 2r of exisiting samples
            //Random unit vector
            ////CREATE A RANDOM VECTOR WITH A DIRECTION WE CAN USE TO SAMPLE POINTS
            FVector sample(FMath::Rand(), FMath::Rand(), FMath::Rand());
            float magnitude = FMath::RandRange(PointRaduis, 2 * PointRaduis);
            sample.operator*=(magnitude);


            //if after k attempts foiund, remove i from the active list

            float col = sample.X / CellSize;
            float row = sample.Y / CellSize;

            //Check neighbors
            for (int32 i = -1; i <= 1; i++)
            {
                for (int32 j = -1; j <= 1; j++)
                {
                    UE_LOG(LogTemp, Error, TEXT("neighbor check should be less than 9 and it is: : %d"), i*j);

                    // get the neighbors position given the indexes
                    int32 index = FMath::FloorToInt((col + i) + (row + j) * xSize);
                    FVector neighbors = BackgroundGrid[index];
                    //check distance between sample and neighbors
                    FVector Distance;
                    float distance = Distance.Distance(sample, neighbors);

                    if (distance < PointRaduis)
                    {
                        //the distance is less than the required item placement, its an invalid spot

                        candidateAccepted = false;
                        break;
                    }
                }
            }

            if (candidateAccepted)
            {
                UE_LOG(LogTemp, Error, TEXT(" location is good"));

                found = true;
                BackgroundGrid[col + row * ySize] = sample;
                ActiveList.Add(sample);
            }

            if (!found)
            {
                UE_LOG(LogTemp, Error, TEXT(" not foundfound"));

                ActiveList.RemoveAt(randomIndex);
            }
        }
    }
}


FVector AOasisGenerator::GetRandomPointInGrid()
{
    //select the sameple point randomly chosen from the grid
    int32 randX = FMath::RandRange(0, xSize);
    int32 randY = FMath::RandRange(0, ySize);

    FVector position;
    position.Set(randX, randY, 0);
    return position;
}

