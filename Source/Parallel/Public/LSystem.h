// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LSystem.generated.h"


USTRUCT(BlueprintType)
struct FRules
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LSystem")
	FString InputValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LSystem")
	FVector Location;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LSystem")
	FRotator Rotation;

	FRules()
	{
		InputValue = "";
		Location = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
	}
	
};


UCLASS()
class PARALLEL_API ALSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	//<initial value, replacement value> for the rules of the LSystem
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LSystem")
	TMap<FString, FString> Axiom;
	
	//Starting Sentence to use 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LSystem")
	FString Sentence;
	
	//TODO: should return a value instead of modifying the sentence directly 
	//Takes the basic Sentence and expands based on rules setup in the Axiom
	UFUNCTION(BlueprintCallable,Category ="LSystem")
	FString Generate(int32 NumberOfGenerations);

	
	UFUNCTION(BlueprintCallable,Category ="LSystem")
	void Turtle();

	UFUNCTION(BlueprintCallable,Category ="LSystem")
	void PotentalStreetGenerator();
	
};

