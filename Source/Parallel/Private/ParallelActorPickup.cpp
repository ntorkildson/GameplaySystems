// Fill out your copyright notice in the Description page of Project Settings.


#include "ParallelActorPickup.h"

// Sets default values
AParallelActorPickup::AParallelActorPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
}

// Called when the game starts or when spawned
void AParallelActorPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParallelActorPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParallelActorPickup::OnUsed()
{
	if(bCanRespawn)
	{
		
	}
	else
	{
		Destroy();
	}
	
}


