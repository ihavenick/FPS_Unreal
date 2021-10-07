// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class APlayerCharacter;

UCLASS()
class DENEMEPROJE_API AWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, Category=Mesh)
	UBoxComponent* CollisionMesh;

	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsHandADS")
	UAnimSequenceBase* Hand_ADS_Idle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsHandADS")
	UAnimSequenceBase* Hand_ADS_Walk;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsHandADS")
	UAnimMontage* Hand_ADS_Fire;
	
	

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsGun")
	UAnimSequenceBase* Gun_Reload;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsHand")
	UAnimSequenceBase* Hand_Reload;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsHand")
	UAnimSequenceBase* Hand_Walk;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsHand")
	UAnimSequenceBase* Hand_Run;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsHand")
	UAnimMontage* Hand_Raise;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsHand")
	UAnimMontage* Hand_Lower;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsGun")
	UAnimMontage* Gun_Fire;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsHand")
	UAnimMontage* Hand_Fire;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AnimsHand")
	UAnimSequenceBase* Hand_Idle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sounds")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FX")
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FX")
	UParticleSystem* ImpactVFX;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	FTimerHandle TimerHandle_HandleReFire;
	

public:
	// UFUNCTION()
	// void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// UFUNCTION()
	// void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Called every frame
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="FireStyle")
	bool bIsAutomaticWeapon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="FireStyle")
	float FireRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AmmoSettings")
	int ClipSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="AmmoSettings")
	int TotalAmmo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category ="FireStyle")
	float WeaponRange;

	void StartFire();

	void StopFire();

	void FireShot();

	UFUNCTION()
	void BeinPickedUp();

};
