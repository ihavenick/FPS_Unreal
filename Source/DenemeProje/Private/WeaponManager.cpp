// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManager.h"

#include "PlayerCharacter.h"


// Sets default values for this component's properties
UWeaponManager::UWeaponManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SelectedWeaponIndex=0;
    bIsEquiped=false;
	CurrentWeapon=nullptr;
}


// Called when the game starts
void UWeaponManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

AWeapon* UWeaponManager::GetCurrentWeapon()
{
	return CurrentWeapon;
}

void UWeaponManager::SelectWeaponWithAxis(int axis)
{
	if (Weapons.Num()<0)
		return;

	if (axis>0)
	{
		SelectedWeaponIndex = SelectedWeaponIndex + 1 % Weapons.Num();
	}
	else if(axis<0)
	{
		if (SelectedWeaponIndex--<0)
		{
			SelectedWeaponIndex=Weapons.Num()-1;
		}
		else
		{
			SelectedWeaponIndex--;
		}
	}
	else
	{
		//WTF
	}

	SelectWeapon(SelectedWeaponIndex);
}

void UWeaponManager::SelectWeapon(int index)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());
	
	if (Weapons.Num()<0)
		return;

	if (Weapons[index])
	{
		CurrentWeapon = Weapons[index];
		CurrentWeapon->AttachToComponent(Player->GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,FName("WeaponSocket"));
		bIsEquiped=true;
	}
}

bool UWeaponManager::DropCurrentWeapon()
{
	return true;
}

bool UWeaponManager::AddWeapon(AWeapon* take)
{
    APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());
	
	if (!take)
		return false;


	Weapons.Add(take);
	if (bIsEquiped)
	{
		take->SetHidden(true);
	}
	else
	{
		take->AttachToComponent(Player->GetHands(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("WeaponSocket"));

		take->BeinPickedUp();
		bIsEquiped=true;
		CurrentWeapon=take;
	}

	
	return true;
}
