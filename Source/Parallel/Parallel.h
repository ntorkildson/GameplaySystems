// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    SingleFire        UMETA(DisplayName = "Single Fire"),
    BurstFire        UMETA(DisplayName = "Burst Fire"),
    AutoFire        UMETA(DisplayName = "Auto Fire"),
    ChargedFire    UMETA(DisplayName = "Charged Fire"),
    Aura            UMETA(DisplayName = "Aura"),
    
};

UENUM(BlueprintType)
enum class EGSAbilityInputID : uint8
{
    // 0 None
    None				UMETA(DisplayName = "None"),
    // 1 Confirm
    Confirm				UMETA(DisplayName = "Confirm"),
    // 2 Cancel
    Cancel				UMETA(DisplayName = "Cancel"),
    // 3 Sprint
    Sprint				UMETA(DisplayName = "Sprint"), 
    // 4 Jump
    Jump				UMETA(DisplayName = "Jump"),
    // 5 PrimaryFire
    PrimaryFire			UMETA(DisplayName = "Primary Fire"),
    // 6 SecondaryFire
    SecondaryFire		UMETA(DisplayName = "Secondary Fire"),
    // 7 Alternate Fire
    AlternateFire		UMETA(DisplayName = "Alternate Fire"),
    // 8 Reload
    Reload				UMETA(DisplayName = "Reload"), 
    // 9 NextWeapon
    NextWeapon			UMETA(DisplayName = "Next Weapon"), 
    // 10 PrevWeapon
    PrevWeapon			UMETA(DisplayName = "Previous Weapon"),
    // 11 Interact
    Interact			UMETA(DisplayName = "Interact"),
    
    Dash                UMETA(DisplayName = "Dash"), 
   
    Slide                UMETA(DisplayName = "Slide")

    //Crouch

    //Prone

    //
};

