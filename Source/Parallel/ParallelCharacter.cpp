// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ParallelCharacter.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "ParallelActorPickup.h"

#include "DrawDebugHelpers.h"
#include "Parallel.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "ParallelItem.h"
#include "PrimaryAbility.h"



#include "Engine/Engine.h"

#include "Net/UnrealNetwork.h"


//////////////////////////////////////////////////////////////////////////
// AParallelCharacter

AParallelCharacter::AParallelCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//TODO: Move this to a playerstate I think.
	AbilitySystemComponent= CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
    AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
    AttributeSet = CreateDefaultSubobject<UMainAttributes>(TEXT("AttributeSet"));
	CurrencySet = CreateDefaultSubobject<UCurrency>(TEXT("CurrencySet"));
	
}

void AParallelCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//initialize our abilities
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		//TODO: check to see if we have character settings stored on a server we need to load	
		//grant base starting stats
		InitializeStats();
		//Grant default abilities to character here;
		
		   	
	}
}

void AParallelCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(AParallelCharacter, Inventory, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(AParallelCharacter, CurrentWeapon, COND_None, REPNOTIFY_Always);
	
}

void AParallelCharacter::BeginPlay()
{
	Super::BeginPlay();

	//spawn default inventory if we have one saved, otherwise just be naked and afraid
	
}

void AParallelCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("Confirm"),
        FString("Cancel"), FString("EGSAbilityInputID"), static_cast<int32>(EGSAbilityInputID::Confirm), static_cast<int32>(EGSAbilityInputID::Cancel)));


	PlayerInputComponent->BindAxis("MoveForward", this, &AParallelCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AParallelCharacter::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AParallelCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AParallelCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AParallelCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AParallelCharacter::TouchStopped);

		//TODO: rework this into a gameplay ability
	PlayerInputComponent->BindAction("InteractWith", IE_Pressed, this, &AParallelCharacter::InteractWith);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AParallelCharacter::OnResetVR);
}


UAbilitySystemComponent* AParallelCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AParallelCharacter::RemoveAbilities_Implementation(AParallelItem* ItemWithAbilities)
{
	if(HasAuthority() && AbilitySystemComponent)
	{
		for(int32 i = 0; i >= ItemWithAbilities->Abilities.Num(); i++)
		{
			auto& Ability = ItemWithAbilities->Abilities[i];
			auto test = Cast<UPrimaryAbility>(ItemWithAbilities->Abilities[i]);

			
		}
	}
}

bool AParallelCharacter::RemoveAbilities_Validate(AParallelItem* ItemWithAbilities)
{
	return true;
}


void AParallelCharacter::RemoveAllAbilities_Implementation()
{
	if(HasAuthority())
	{
		if(AbilitySystemComponent)
		{
			AbilitySystemComponent->ClearAllAbilities();
		}
		
	}	
}

bool AParallelCharacter::RemoveAllAbilities_Validate()
{
	return true;
}

void AParallelCharacter::RemoveSpecificAbility_Implementation(TSubclassOf<UGameplayAbility> AbilityToRemove)
{
	if(HasAuthority() && AbilityToRemove)
	{	//TODO: convert from abilityspec to abilityspechandle?
		//AbilitySystemComponent->ClearAbility(AbilityToRemove);
		
	}
}

bool AParallelCharacter::RemoveSpecificAbility_Validate(TSubclassOf<UGameplayAbility> AbilityToRemove)
{
	return true;
}

void AParallelCharacter::GiveSpecificAbility_Implementation(TSubclassOf<UGameplayAbility> AbilityToGive)
{
	if(HasAuthority() && AbilityToGive)
	{
		auto* Ability = Cast<UPrimaryAbility>(AbilityToGive.GetDefaultObject());
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability,1,static_cast<int32>(Ability->ItemLocation),this));
	}
}
	
bool AParallelCharacter::GiveSpecificAbility_Validate(TSubclassOf<UGameplayAbility> AbilityToGive)
{
	return true;
}

void AParallelCharacter::GiveAbilities_Implementation(AParallelItem* ItemWithAbilities)
{
	if(HasAuthority() && AbilitySystemComponent)
	{
		for(auto& Ability : ItemWithAbilities->Abilities)
		{

			//We need the ability to grant, and what firing location it goes in(primary/secondary/tertiary)
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability,1,static_cast<int32>(Ability.GetDefaultObject()->ItemLocation),this));

		}
		
	}		
}

bool AParallelCharacter::GiveAbilities_Validate(AParallelItem* ItemWithAbilities)
{
	return true;
}

void AParallelCharacter::InitializeStats_Implementation()
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
			UE_LOG(LogTemp, Warning, TEXT("Stats Should be Added") );
				

		}

		
	}
}

bool AParallelCharacter::InitializeStats_Validate()
{
	return  true;
}


//TODO: remove VR stuff
void AParallelCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AParallelCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AParallelCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AParallelCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AParallelCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AParallelCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		//TODO: simplify and extend
		//Value = Value * GetMoveSpeedFromAbilitySystemModifications();

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AParallelCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		//TODO: Simplify and extend
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}


//TODO: add final getter functions for attributes and currency
float AParallelCharacter::GetLife()
{
	if(AttributeSet)
	{
		return AttributeSet->GetLife();
	}
	return 0.0f;
}

float AParallelCharacter::GetMaxLife()
{
	if(!AttributeSet)
		return 0.0f;
	return AttributeSet->GetMaxLife();
}

float AParallelCharacter::GetMana()
{
	if(!AttributeSet)
		return 0.0f;
	return AttributeSet->GetMana();
}

float AParallelCharacter::GetMaxMana()
{
	if(!AttributeSet)
		return 0.0f;
	return AttributeSet->GetMaxMana();
}

float AParallelCharacter::GetMaxEnergy()
{
	if(!AttributeSet)
		return 0.0f;
	return AttributeSet->GetMaxEnergy();
	
}

float AParallelCharacter::GetPhysicalStrength()
{
	if(!AttributeSet)
		return 0.0f;
	return AttributeSet->GetPhysicalStrength();
}

float AParallelCharacter::GetPhysicalDexterity()
{
	if(!AttributeSet)
		return 0.0f;
	return AttributeSet->GetPhysicalDexterity();
}

float AParallelCharacter::GetPhysicalEndurance()
{
	if(!AttributeSet)
	return 0.0f;
	return AttributeSet->GetPhysicalEndurance();
}

float AParallelCharacter::GetMinDamage()
{
	if(!AttributeSet)
		return 0;
	return AttributeSet->GetBaseDamage();
}

float AParallelCharacter::GetCritChance()
{
	if(!AttributeSet)
		return 0;
	return AttributeSet->GetCritChance();
}

float AParallelCharacter::GetCritMultiplier()
{
	if(!AttributeSet)
		return 0;
	return AttributeSet->GetCritDamage();
}

float AParallelCharacter::GetAttackSpeed()
{
	if(!AttributeSet)
		return 0;
	//return AttributeSet->GetAttackSpeed();
	return 1;
}

float AParallelCharacter::GetEnergy()
{
	if(AttributeSet)
	{
		return AttributeSet->GetEnergy();
	}
	else return -1.f;
	
}



/*TODO: Currency system needs to be extended drastically*/

float AParallelCharacter::GetWood()
{
	if(CurrencySet)
	{
		return CurrencySet->GetWood();
	}
	else return -1.f;
	
}

float AParallelCharacter::GetIron()
{
	if(!CurrencySet)
		return 0;
	return CurrencySet->GetIron();
}

float AParallelCharacter::GetStone()
{
	if(CurrencySet)
	{
		return CurrencySet->GetStone();
	}
	else return -1.0f;
}


/* TODO: Inventory System*/
void AParallelCharacter::EquipItem(AParallelItem* ItemToEquip)
{
	if(ItemToEquip)
		if(ItemToEquip == CurrentWeapon)
			return;
		if(HasAuthority())
		{
			SetCurrentWeapon(ItemToEquip, CurrentWeapon);
		}
	else
	{
		ServerEquipItem(ItemToEquip);
	}
}

void AParallelCharacter::ServerEquipItem_Implementation(AParallelItem* ItemToEquip)
{

	EquipItem(ItemToEquip);
	/*
	{	//if we have an item and an ability on the item
		if(ItemToEquip)
		{	//use the appropriate location(TODO: implement more locations)

			if(CurrentWeapon)
			{
				RemoveSpecificAbility(CurrentWeapon->PrimaryAbility);
				//Unattach weaponmesh and destroy it
				CurrentWeapon = nullptr;
			}
					
			//Equip the new Mainhand weapon
					
			CurrentWeapon = ItemToEquip;
			GiveSpecificAbility(CurrentWeapon->PrimaryAbility);
			//play some equip item animation
					
			//Attach WeaponMesh to socket
			CurrentWeapon->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale,WeaponSocket);
					
			//Remove from inventory
			RemoveItem(ItemToEquip);
					
		}
				
				
	}
	*/
}

bool AParallelCharacter::ServerEquipItem_Validate(AParallelItem* ItemToEquip)
{
	return true;
}

void AParallelCharacter::SetCurrentWeapon(AParallelItem* NewWeapon, AParallelItem* LastWeapon)
{	
	PreviousWeapon = LastWeapon;
	AParallelItem* LocalLastWeapon = nullptr;
	if(LastWeapon)
	{
		for(int32 i = 0; i > CurrentWeapon->Abilities.Num(); i++)
		{
			RemoveSpecificAbility(CurrentWeapon->Abilities[i]);
		}
		//RemoveSpecificAbility(CurrentWeapon->PrimaryAbility);
		LocalLastWeapon = LastWeapon;
		
	}
	
	else if(NewWeapon != CurrentWeapon)
	{
		LocalLastWeapon = CurrentWeapon;
	}

	bool bHasPrevWeapon = false;
	if(LocalLastWeapon)
	{
		//LocalLastWeapon->OnUnEquip();
		bHasPrevWeapon =true;
	}
	CurrentWeapon = NewWeapon;
	if(NewWeapon)
	{
		GiveAbilities(NewWeapon);
		//GiveSpecificAbility(CurrentWeapon->PrimaryAbility);
		NewWeapon->SetOwner(this);
		//Remove from inventory
		RemoveItem(NewWeapon);
		
	}
	SwapToNewWeaponMesh();
		
}

void AParallelCharacter::SwapToNewWeaponMesh()
{
		/*
		 * TODO: previous mesh is destroyed or removed entirely
		 * 
		 */
	if(PreviousWeapon)
	{
		PickupItem(PreviousWeapon);
		
		//PreviousWeapon goes to storage
		//PreviousWeapon->AttachMeshToPawn(EInventorySlot::back);
	}
	if(CurrentWeapon)
	{

		CurrentWeapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,WeaponSocket);

	}
	
}

void AParallelCharacter::UnEquipItem_Implementation(AParallelItem* ItemToUnEquip)
{
	//main weapon is "destroyed"
	CurrentWeapon->Destroy(true);
	//JUST TO MAKE SURE
	CurrentWeapon = nullptr;
	
	//efffectively adds to inventory
	PickupItem(ItemToUnEquip);
	
}

bool AParallelCharacter::UnEquipItem_Validate(AParallelItem* ItemToUnEquip)
{
	if(ItemToUnEquip)
	{
		return true;
	}
	return false;
}

void AParallelCharacter::PickupItem_Implementation(class AParallelItem* ItemToPickup)
{
	
	if(ItemToPickup && HasAuthority())
	{
		
		if(ItemToPickup->bIsStackable && Inventory.Contains(ItemToPickup))
		{

			int32 index = Inventory.Find(ItemToPickup);
			Inventory[index]->ItemQty+=ItemToPickup->ItemQty;

		}
		else if(!CurrentWeapon)
		{
			EquipItem(ItemToPickup);
		}
		else
		{
			
			Inventory.Add(ItemToPickup);


		}
                             
	}
}
                 
bool AParallelCharacter::PickupItem_Validate(AParallelItem* ItemToPickup)
{
	return true;
}

void AParallelCharacter::RemoveItem_Implementation(AParallelItem* ItemToRemove)
{
	if(ItemToRemove && HasAuthority())
	{
		if(Inventory.Contains(ItemToRemove))
		{
			Inventory.RemoveSingle(ItemToRemove);
		}
		
	}
}

bool AParallelCharacter::RemoveItem_Validate(AParallelItem* ItemToRemove)
{
	return true;
}

void AParallelCharacter::DropItem_Implementation(AParallelItem* ItemToDrop)
{
	if(HasAuthority())
	{
		
		if(!ItemToDrop)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red,TEXT("No item to drop for some rason"));
			return;
		}
		//trace for drop location

		FVector CameraLocation;
		FRotator CameraRotation;
		
		
		Controller->GetPlayerViewPoint(CameraLocation,CameraRotation);
		float DropDistance = 500;
		FVector TraceEnd = CameraLocation + (FollowCamera->GetForwardVector() * DropDistance);
	
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
	
		FHitResult Hit;
		DrawDebugLine(GetWorld(), CameraLocation, TraceEnd, FColor::Green, false, 12, 0, 1);
		
		GetWorld()->LineTraceSingleByChannel(Hit, CameraLocation, TraceEnd, ECC_WorldDynamic, TraceParams);
		FVector SpawnLocation;
		//spawn dropped weapon
		if(Hit.bBlockingHit)
		{
			SpawnLocation = Hit.ImpactPoint + (Hit.ImpactNormal *20);
		}
		else
		{//so we can 'throw' stuff into the air
			SpawnLocation = TraceEnd;
		}

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		
		AParallelActorPickup* NewWeaponPickup = GetWorld()->SpawnActor<AParallelActorPickup>(ItemToDrop->WeaponPickupClass, SpawnLocation, FRotator::ZeroRotator, SpawnInfo);
		if(NewWeaponPickup)
		{
			GEngine->AddOnScreenDebugMessage(-1,5 ,FColor::Red,TEXT("ActorPickupSpawned"));

		}
		//removes it from the inventory;
		RemoveItem(ItemToDrop);
	}
}

bool AParallelCharacter::DropItem_Validate(AParallelItem* ItemToDrop)
{
	return true;
}

void AParallelCharacter::InteractWith()
{
	if(HasAuthority())
	{
		AParallelActorPickup* Usable = GetItemInView();
		if(Usable)
		{
			//Play pickup sound
			//spawn the actor

			FActorSpawnParameters SpawnInfo;
			AParallelItem* NewItem = GetWorld()->SpawnActor<AParallelItem>(Usable->OurItem,SpawnInfo);
			//add the item to our inventory
			PickupItem(NewItem);
			Usable->OnUsed();	
		}
	}
	else
	{
		ServerInteractWith();
	}
	
}

void AParallelCharacter::ServerInteractWith_Implementation()
{
	InteractWith();
}

bool AParallelCharacter::ServerInteractWith_Validate()
{
	return true;
}

AParallelActorPickup* AParallelCharacter::GetItemInView()
{
	//TODO: Move to gameplayability
	//TODO: make a sphere trace because line traces are a bitch
	FVector StartLocation;
	FRotator LookDirection;

	Controller->GetPlayerViewPoint(StartLocation, LookDirection);
	FVector Direction = LookDirection.Vector();
	FVector TraceEnd = StartLocation + Direction * 800;

	FCollisionQueryParams TraceParams;
	TraceParams.bTraceComplex = false;

	FHitResult Hit;
	DrawDebugLine(GetWorld(), StartLocation, TraceEnd, FColor::Green, false, 12, 0, 1);

	GetWorld()->LineTraceSingleByChannel(Hit,StartLocation, TraceEnd,ECC_Visibility,TraceParams);
	return Cast<AParallelActorPickup>(Hit.GetActor());
	
}


float AParallelCharacter::OnDamaged()
{
	//most of this should be moved to the gameplayCue system
	//play hit animation
	//play hit material effects
	//play hit sound effects
	//play hit particle effects
	//
	//check to see if health > 0
		//DEATH
	OnDeath();

	return 1.0f;
}




void AParallelCharacter::OnHealthChange()
{
	//update health bar
	//UE_LOG(LogTemp,Error,TEXT("Health Changed: %f"),GetLife());
	
}



void AParallelCharacter::OnDeath()
{
	//Die
	//unpossess pawn
	//start timer for repsawn
	//create a new pawn  to possess
	//possess new pawn when its ready
	
	//cancel all abilities
//	AbilitySystemComponent->CancelAllAbilities();
	//remove character abilities
//	RemoveAllAbilities();
//	AbilitySystemComponent->RemoveAllGameplayCues();

		
	//play death animation
	
	
	//Drop Loot
	
	//Drop experience(Unless we're a Player)
	
	//RespawnSystem

	//Destroys this pawn
	//Destroy();
	
}

