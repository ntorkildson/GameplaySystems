// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Abilities/GameplayAbility.h"
#include "ParallelTargetType.h"

#include "Parallel/Parallel.h"



#include "PrimaryAbility.generated.h"

/**
 * TODO: ActivateOnGranted should be moved to the struct, we currently cannot activate stats with this setp
 */

//ALLows us to hit with multiple damage types with different targeting
USTRUCT(BlueprintType)
struct FParallelEffectContainer
{
	GENERATED_BODY()
public:
		FParallelEffectContainer(){}
			
	//all the gameplay Effects we are going to apply to the target
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay | Combat")
    TArray<TSubclassOf<UGameplayEffect>> TargetGameplayEffectClasses;

	//what kind of targeting to use(Direct, PBAOE, AOE, Projectile, other...)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay | Combat")
    TSubclassOf<UParallelTargetType> TargetType;
	
};


UCLASS()
class PARALLEL_API UPrimaryAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPrimaryAbility();
	
	/* Epic uses this as a begin play
	* Use this for activating abilities if bActiveOnGranted = true;
	* */
	
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	//activate ability
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	//TOOD: finish implementing how we use our abilities
	UFUNCTION(BlueprintCallable,Category = "Gameplay Abilities")
	void UseAbility();
	
	
	//should be activated on equipped(auras and immediate usage items like that)
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Gameplay | Defaults")
	bool bActivateOnGranted = false;
	
	//Not Currently Implemented
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = "Gameplay | Defaults")
	TSubclassOf<class UParallelGameplayEffect> OwnerAttributeMods;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	EGSAbilityInputID ItemLocation;

		
	//TODO: possibly use an array for chaining montages or randomly picking an animation
	//animation montage to play(possibly use an array and ranomlypick or combos?
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay | Effects")
    UAnimMontage* UseAnimation;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay | Effects")
	USoundBase* UseSound;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay | Effects")
	UParticleSystem* UseEffect;
		
	//TODO: Currently we arent using this, but its here for future usage..maybe...
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay | Defautls")
    TSubclassOf<class AActor> SpawnableActor;
	
	
	//allows mutliple damage types to be used on the player
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Gameplay | Combat")
	TArray<FParallelEffectContainer> Container;
	

	/** Computed target data */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
    FGameplayAbilityTargetDataHandle TargetData;

	/** List of gameplay effects to apply to the targets */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
    TArray<FGameplayEffectSpecHandle> TargetGameplayEffectSpecs;
	
		
	
};
