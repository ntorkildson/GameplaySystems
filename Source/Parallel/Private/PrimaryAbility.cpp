// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryAbility.h"

#include "AbilitySystemComponent.h"
#include "ParallelAbilityTypes.h"
#include "ParallelTargetType.h"
#include "Parallel/ParallelCharacter.h"


UPrimaryAbility::UPrimaryAbility()
{
    //TODO: set defaults here, can include tags or instance properties, or replciation or whatever...
    //instancing policy, ability tags, blocking tags(death/stun/etc.)
    
}


void UPrimaryAbility::OnAvatarSet(const FGameplayAbilityActorInfo *ActorInfo, const FGameplayAbilitySpec &Spec)
{
    Super::OnAvatarSet(ActorInfo, Spec);
    //if we should use this ability immediately(auras)
    if(bActivateOnGranted)
    {
        bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, true);
        if(!ActivatedAbility)
        {
            UE_LOG(LogTemp,Display,TEXT("Shit broke"));
        }
        
    }  
    
}


void UPrimaryAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

   
   
}


  void UPrimaryAbility::UseAbility()
{
    //get owning actor and ability system
    AParallelCharacter* OwningCharacter = Cast<AParallelCharacter>(GetOwningActorFromActorInfo());
    UAbilitySystemComponent* OwningAbilitySystem = OwningCharacter->GetAbilitySystemComponent();

    if(OwningAbilitySystem)
    {
        
        for(int32 i = 0; Container.Num() > i; ++i)
        {
            //if we have a targeting type selected:            
            UParallelTargetType* NewTargets =  Container[i].TargetType.GetDefaultObject();
            if(NewTargets)
            {
                
                //all the hits we had
                TArray<FHitResult> TargetHitResult;
                //all the actors we hit
                TArray<AActor*> TargetGroup;
                
                //get a list of all the targets we are hitting with this ability
                NewTargets->GetTargets(OwningCharacter, TargetHitResult, TargetGroup);

                /*For combat attacks*/         
                for(FHitResult& NewHits : TargetHitResult)
                {
                    
                    //create the array we can add hit targets to it
                    FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
                    //for each of the hit results in the array, add them to TargetData.Add(NewData)
                    NewData->TargetActorArray.Append(TargetGroup);
                    TargetData.Add(NewData);


            
             
                    //for each GameplayEffect we want to apply, make an outgoing effect so we can apply it later
                    for(TSubclassOf<UGameplayEffect>& EffectClass : Container[i].TargetGameplayEffectClasses)
                    {
                        TargetGameplayEffectSpecs.Add(MakeOutgoingGameplayEffectSpec(EffectClass,1));

                    }
                    
                    //for each actor in TargetData applygameplayEffectSPec to them, which should deal damage...
                    for(FGameplayEffectSpecHandle& SpecHandle : TargetGameplayEffectSpecs)
                    {
                        
                        //applyGameplayEffectTo all targets which is TargetData
                        K2_ApplyGameplayEffectSpecToTarget(SpecHandle,TargetData);
            
                    }
                    //clears target data so we dont hit them multiple times or apply our buffs to them
                    TargetData.Clear();
                    TargetHitResult.Empty();
                    TargetGroup.Empty();
                }
            }
        }
    }
}

    
