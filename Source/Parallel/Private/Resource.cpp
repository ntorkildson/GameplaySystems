// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource.h"

#include "AbilitySystemComponent.h"

// Sets default values
AResource::AResource()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent= CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);


	AttributeSet = CreateDefaultSubobject<UMainAttributes>(TEXT("AttributeSet"));
	CurrencySet = CreateDefaultSubobject<UCurrency>(TEXT("CurrencySet"));
	
}

// Called when the game starts or when spawned
void AResource::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AResource::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}


UAbilitySystemComponent* AResource::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool AResource::ReactToTrigger()
{
	return true;
}

float AResource::OnHealthChanged(float ChangedAmount) const
{
	//UE_LOG(LogTemp,Error,TEXT("Child Interface called %f"),ChangedAmount);

	return ChangedAmount;
}

void AResource::InitializeStats_Implementation()
{
	//run this on the server
	if (GetLocalRole() == ROLE_Authority)
	{

		//apply attributes from default setup

		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeReference, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
				

		}

		
	}
}

bool AResource::InitializeStats_Validate()
{
	return true;
}

void AResource::OnDamaged(float IncommingDamage)
{
	UE_LOG(LogTemp,Error,TEXT("Incomming Damage is: %f"),IncommingDamage);
	TempDamageVar = IncommingDamage;
	//GetTargetWhoHitUs and give them money
}

float AResource::GetLife()
{
	if(AttributeSet)
	{
		return AttributeSet->GetLife();
	}
	return -1.f;
}



void AResource::Respawn()
{
	
}

