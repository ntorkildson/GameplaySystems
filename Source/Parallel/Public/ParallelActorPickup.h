// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParallelActorPickup.generated.h"

UCLASS()
class PARALLEL_API AParallelActorPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AParallelActorPickup();

	/*Almost all of this is built in blueprints, and this will probably be deleted as a Parent class*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//ItemData asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Item")
	TSubclassOf<class AParallelItem> OurItem;

	bool bCanRespawn = false;
	
	void OnUsed();	

};

