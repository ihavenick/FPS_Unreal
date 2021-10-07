// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Components/ActorComponent.h"
#include "WeaponManager.generated.h"

class APlayerCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DENEMEPROJE_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()

	
	
private:
	TArray<AWeapon *> Weapons;
	int SelectedWeaponIndex;
	AWeapon* CurrentWeapon;
	
	
public:	
	// Sets default values for this component's properties
	UWeaponManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Test")
	bool bIsEquiped;
	
	
	UFUNCTION(BlueprintCallable)
	AWeapon* GetCurrentWeapon();
	
	// UFUNCTION()
	// void ShootFromCurrentWeapon();

	UFUNCTION()
	void SelectWeaponWithAxis(int axis);

	UFUNCTION()
	void SelectWeapon(int index);

	UFUNCTION()
	bool DropCurrentWeapon();

	UFUNCTION()
	bool AddWeapon(AWeapon* take);
	

		
};
