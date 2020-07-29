// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainAttributes.h"
#include "Currency.h"
#include "DamageDealingInt.h"


#include "Resource.generated.h"


UCLASS()
class PARALLEL_API AResource : public AActor, public IAbilitySystemInterface, public IDamageDealingInt
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AResource();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Our ability system component.
	UPROPERTY(BlueprintReadOnly, Category = "Character Base | Ability System Component")
	class UAbilitySystemComponent* AbilitySystemComponent;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Helper function to get our ability system component (Used by the IAbilitySystemInterface).
	UFUNCTION(BlueprintPure, Category = "Character Base | Ability System Component")
    UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual bool ReactToTrigger() override;

	virtual float OnHealthChanged(float ChangedAmount) const override;
	
	//basically just health for these objects, maybe armor
	UPROPERTY()
	UMainAttributes* AttributeSet;

		//TOOD: use this to determine how much we can mine from this object.
	UPROPERTY()
	UCurrency* CurrencySet;


	//gameplayEffect with the default stats we have as a blank character
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Defaults")
	TSubclassOf<class UGameplayEffect> DefaultAttributeReference;
		
	//Grants our resources the stats they need
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void InitializeStats();

	void OnDamaged(float IncommingDamage);

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category="Damage")
	float TempDamageVar;
	
	UFUNCTION(BlueprintCallable, Category="Damage")
    float GetLife();
	
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Defaults")
	float DamageTaken;

	/*Once destroyed, respawn object*/
	int32 RespawnTimer;

	void Respawn();
	
	
	
};
