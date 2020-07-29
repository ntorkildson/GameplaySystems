// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAttributes.h"
#include "Net/UnrealNetwork.h"

#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Parallel/ParallelCharacter.h"
#include "Resource.h"

UMainAttributes::UMainAttributes()

{
   // Life = MaxLife; //+ PHysicalStrength * (PhysicalEndurance *2) or something
    //Mana = MaxMana; //MentalStrength && stats
    //Energy = MaxEnergy; // PhysicalEndurance/MentalEndurance
    
    
    //TODO: calculate reactive stats (critChance = PhysicalDexterity * somevalue or whatever)
    
}




void UMainAttributes::PreAttributeChange(const FGameplayAttribute &Attribute, float &NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);
    //Maintain Percentage difference if max values change for some reason
    if(Attribute == GetMaxLifeAttribute())
    {
        AdjustAttributeForMaxChange(Life,MaxLife,NewValue,GetLifeAttribute());
    }
    else if(Attribute == GetMaxManaAttribute())
    {
        //TODO:
    }
    else if (Attribute == GetMaxEnergyAttribute())
    {
        
    }
    
}


void UMainAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data)
{
    Super::PostGameplayEffectExecute(Data);

    FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
    UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
    const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

    // Get the Target actor, which should be our owner
    AActor* TargetActor = nullptr;
    AController* TargetController = nullptr;
    AParallelCharacter* TargetCharacter = nullptr;
    AResource* TargetResource = nullptr;

  
    
    if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    {
        TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
        TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
        TargetCharacter = Cast<AParallelCharacter>(TargetActor);



    }
  
    if(Data.EvaluatedData.Attribute == GetBaseDamageAttribute())
    {
        //Handle damage taken, Set New Life total, Trigger handle damage and health changed on Character
        //Get Source Actor, SourceController, SourceCharacter
        FHitResult HitResult;
        if(Context.GetHitResult())
        {
            HitResult = *Context.GetHitResult();
        }
    
        // Store a local copy of the amount of damage done and clear the damage attribute
        const float LocalDamage = GetBaseDamage();
        SetBaseDamage(0.f);
        
        if(LocalDamage > 0.0f)
        {
            //apply health change, clamp it
            float OldLife = GetLife();
            SetLife(FMath::Clamp(OldLife - LocalDamage, 0.0f,GetMaxLife()));
          //  UE_LOG(LogTemp,Warning,TEXT(" Localized Damage is:  %f"),OldLife - LocalDamage);

            bool bIsImplemented = TargetActor->GetClass()->ImplementsInterface(UDamageDealingInt::StaticClass()); // bIsImplemented will be true if OriginalObject implements UReactToTriggerInterface.
            IDamageDealingInt* ReactingObjectA = Cast<IDamageDealingInt>(TargetActor); // ReactingObject will be non-null if OriginalObject implements UReactToTriggerInterface.
            if(ReactingObjectA)
            {
                ReactingObjectA->OnHealthChanged(324);
                
            }
            
            
            if(TargetCharacter)
            {
                TargetCharacter->OnDamaged();
                //call for all health changes
                
                TargetCharacter->OnHealthChange();
            }
            if(TargetResource)
            {
                TargetResource->OnHealthChanged(LocalDamage);
                //TODO: Convert this to an interface
                TargetResource->OnDamaged(LocalDamage);
            }
            
        }
    }
    
    //Handle life changes not related to damage, such as health regen or max health increases
    else if(Data.EvaluatedData.Attribute == GetLifeAttribute())
    {
        SetLife(FMath::Clamp(GetLife(), 0.f, GetMaxLife()));
        //  UE_LOG(LogTemp,Log,TEXT("Current Life is: %f"),GetLife());

        //   UE_LOG(LogTemp,Log,TEXT("Life should be clamped to no more than %f"),GetMaxLife());
        if(TargetCharacter)
            TargetCharacter->OnHealthChange();
        else if(TargetResource)
            TargetResource->OnHealthChanged(GetLife());
    }
    
    //handle mana changes, min and max values, etc.
    else if (Data.EvaluatedData.Attribute ==  GetManaAttribute())
    {
    
        //SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
        //TargetCharacter->OnManaChanged();
    }
    else if (Data.EvaluatedData.Attribute ==  GetEnergyAttribute())
    {
        
    }
    else if(Data.EvaluatedData.Attribute == GetPhysicalStrengthAttribute())
    {
        //might move this to Pre change but....
        /*
         *Once this is updated, we can update relevant stats as well, such sa physical damage, crit damage and various things like that.
         *I think...
         */
        //Also clamp values to make sure they dont go below 1 if they are being affected negatively.
    }
    else if(Data.EvaluatedData.Attribute == GetActionsAttribute())
    {
        SetActions(FMath::Clamp(GetActions(), 0.f, GetMaxActions()));

    }
  
}

void UMainAttributes::OnRep_Actions(const FGameplayAttributeData& OldActions)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, Actions,OldActions);
}

void UMainAttributes::OnRep_MaxActions(const FGameplayAttributeData& OldMaxActions)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, MaxActions,OldMaxActions);
}

//TODO: Update the macro to use the proper variables after the upgrade
void UMainAttributes::OnRep_Life(const FGameplayAttributeData& OldLife)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, Life,OldLife);


}

void UMainAttributes::OnRep_MaxLife(const FGameplayAttributeData& OldMaxLife )
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, MaxLife,OldMaxLife);
}

void UMainAttributes::OnRep_Mana()
{
        GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, Mana,Mana);

}

void UMainAttributes::OnRep_MaxMana()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, MaxMana,MaxMana);

}

void UMainAttributes::OnRep_MaxEnergy()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, MaxEnergy,MaxEnergy);

}


void UMainAttributes::OnRep_Energy()
{
        GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, Energy,Energy);

}

void UMainAttributes::OnRep_PhysicalStrength()
{
        GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, PhysicalStrength,PhysicalStrength);

}

void UMainAttributes::OnRep_PhysicalDexterity()
{
        GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, PhysicalDexterity, PhysicalDexterity);

}

void UMainAttributes::OnRep_PhysicalEndurance()
{
        GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, PhysicalEndurance,PhysicalEndurance);

}

void UMainAttributes::OnRep_MentalStrength()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, MentalStrength,MentalStrength);
}

void UMainAttributes::OnRep_MentalDexterity()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, MentalDexterity,MentalDexterity);
}

void UMainAttributes::OnRep_MentalEndurance()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, MentalEndurance,MentalEndurance);
}

void UMainAttributes::OnRep_BaseDamage()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, BaseDamage, BaseDamage);
}

void UMainAttributes::OnRep_CritChance()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, CritChance, CritChance);
}

void UMainAttributes::OnRep_CritDamage()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, CritDamage,CritDamage);
}

void UMainAttributes::OnRep_PhysicalArmor()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, PhysicalArmor,PhysicalArmor);
}

void UMainAttributes::OnRep_SlashingDefense()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, SlashingDefense,SlashingDefense);

}

void UMainAttributes::OnRep_PhysicalDodge()
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UMainAttributes, PhysicalDodge,SlashingDefense);
}

void UMainAttributes::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
    const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
    UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
    const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
    if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
    {
        // Change current value to maintain the current Val / Max percent
        const float CurrentValue = AffectedAttribute.GetCurrentValue();
        float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

        AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
    }
}


void UMainAttributes::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UMainAttributes, Life);
    DOREPLIFETIME(UMainAttributes, MaxLife);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, Mana, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, MaxMana, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, Actions, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, MaxActions, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, Energy, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, MaxEnergy, COND_None, REPNOTIFY_Always);

    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, PhysicalStrength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, PhysicalDexterity, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, PhysicalEndurance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, MentalStrength, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, MentalDexterity, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, MentalEndurance, COND_None, REPNOTIFY_Always);
    
    //combat stats
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, BaseDamage, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, CritChance, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, CritDamage, COND_None, REPNOTIFY_Always);

    //Defensive Stats
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, PhysicalArmor, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, PhysicalDodge, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UMainAttributes, SlashingDefense, COND_None, REPNOTIFY_Always);

    
}
