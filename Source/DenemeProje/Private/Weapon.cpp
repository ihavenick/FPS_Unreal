// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	WeaponRange = 20000.f;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	bIsAutomaticWeapon=true;
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	
	//CollisionMesh->InitializeComponent();
	CollisionMesh->SetGenerateOverlapEvents(true);
	//CollisionMesh->SetupAttachment(Mesh);
	CollisionMesh->SetBoxExtent(FVector(20.f,20.f,20.f));
	CollisionMesh->SetCollisionProfileName("Trigger");

	
	
	RootComponent = Mesh;
	// Mesh1P->SetOnlyOwnerSee(true);
	// Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	// Mesh1P->bCastDynamicShadow = false;
	// Mesh1P->CastShadow = false;
	// Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	// Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
}




// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::BeinPickedUp()
{
	// UAnimInstance* WeaponAnimInstance = Mesh->GetAnimInstance();
	// if (WeaponAnimInstance)
	// {
	// 	WeaponAnimInstance->Montage_Play(raise, 1.f);
	// }
	CollisionMesh->SetGenerateOverlapEvents(false);
}

void AWeapon::StartFire()
{
	FireShot();
	if (bIsAutomaticWeapon)
		GetWorldTimerManager().SetTimer(TimerHandle_HandleReFire,this,&AWeapon::FireShot,FireRate,true);
}

void AWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_HandleReFire);
}

void AWeapon::FireShot()
{
	FHitResult Hit;

	const FVector TraceStartLoc = Mesh->GetSocketLocation(FName("Fire_FX_Slot"));
	const FVector TraceEndLoc   = (Mesh->GetForwardVector() * WeaponRange) * TraceStartLoc;

	FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace),false,this);

	if(GetWorld()->LineTraceSingleByChannel(Hit,TraceStartLoc,TraceEndLoc,ECC_Visibility, QueryParams))
	{
		if(ImpactVFX)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactVFX, FTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint));
		}
	}

	if (MuzzleFlash)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),MuzzleFlash,TraceStartLoc);
	}
	

	
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,FireSound,GetActorLocation());
	}
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());
	
	if (Gun_Fire&&Hand_Fire&&Player)
	{
		UAnimInstance* WeaponAnimInstance = Mesh->GetAnimInstance();
		if (WeaponAnimInstance)
		{
			Player->PlayAnimMontage(Player->bIsAimDownSighs ? Hand_ADS_Fire : Hand_Fire);
			WeaponAnimInstance->Montage_Play(Gun_Fire, 1.f);
		}
	}
}
