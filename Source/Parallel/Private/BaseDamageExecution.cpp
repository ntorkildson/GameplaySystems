// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseDamageExecution.h"
#include "Parallel/Public/BaseDamageExecution.h"


#include "GameplayEffectExecutionCalculation.h"
#include "MainAttributes.h"

//#include "Parallel/Public/BaseDamageExecution.h"


struct BaseDamageStatics
{
    DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalArmor);
    DECLARE_ATTRIBUTE_CAPTUREDEF(BaseDamage);
    //base weapon stats:
        //damage
        //crit chance
        //crit damage
    //target defenses:
        //dodge/parry/block chance(whats the difference or can we just dick around with them all and give the illusion of options?
        //armor based on the appropriate damage type(slashing/fire/etc.)
        //global defenses
        //energyshield
        
        
        
    BaseDamageStatics()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributes, PhysicalArmor, Target,false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UMainAttributes, BaseDamage, Source, false);
        
    }
    
};


static const BaseDamageStatics& DamageStatics()
{
    static BaseDamageStatics DmgStatics;
    return DmgStatics;
}


UBaseDamageExecution::UBaseDamageExecution()
{
    //Capture the relevant attribute definitions
    RelevantAttributesToCapture.Add(DamageStatics().PhysicalArmorDef);
    RelevantAttributesToCapture.Add(DamageStatics().BaseDamageDef);
}


void UBaseDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
   
    UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
    UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

    AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->AvatarActor : nullptr;
    AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->AvatarActor : nullptr;

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    // Gather the tags from the source and target as that can affect which buffs should be used
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    float TargetArmor = 1.f;
    float UnmitigatedDamage = 0.0f;

    
    
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalArmorDef, EvaluationParameters, TargetArmor);
    TargetArmor = FMath::Max<float>(TargetArmor, 0.0);
    
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BaseDamageDef, EvaluationParameters, UnmitigatedDamage);
    
    //we can request a gameplayTag(like mining type system like this:
    //if(WeaponTypeTag == FGameplayTag::RequestGameplayTag(FName("Weapon.Type.Mining"))) give the player some currency or something?

    

    //we can access the hit result for limb damage like this;
    //const FHitResult* Hit = Spec.GetContext().GetHitResult();
    //if(Hit->BoneName == "headBoneName") { increase damage or something }


    //turn to funciton when it gets more complicated
    float MitigatedDamage = (UnmitigatedDamage) * (100/100+TargetArmor);

    
    if(MitigatedDamage > 0.f)
    {
        OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().BaseDamageProperty, EGameplayModOp::Additive, MitigatedDamage));

    }
    

}

