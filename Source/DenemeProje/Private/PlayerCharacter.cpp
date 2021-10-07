// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "WeaponManager.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	
	
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	MeshHand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMeshHand"));
	MeshHand->SetOnlyOwnerSee(true);
	MeshHand->SetupAttachment(FirstPersonCameraComponent);
	MeshHand->bCastDynamicShadow = false;
	MeshHand->CastShadow = false;
	//MeshHand->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	MeshHand->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnOverlapBegin);

	
	// WeaponManager = CreateDefaultSubobject<UWeaponManager>("WeaponManager");
	// AddOwnedComponent(WeaponManager);
}

USkeletalMeshComponent* APlayerCharacter::GetHands()
{
	return MeshHand;
}


// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponManager    = Cast<UWeaponManager>(GetComponentByClass(UWeaponManager::StaticClass()));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::AttackStart);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::AttackStop);

	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &APlayerCharacter::PickUp);

	PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &APlayerCharacter::Zoom);
	PlayerInputComponent->BindAction("Zoom", IE_Released, this, &APlayerCharacter::ZoomOut);


	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void APlayerCharacter::ZoomOut()
{
	bIsAimDownSighs=false;
}

void APlayerCharacter::Zoom()
{
	if (WeaponManager)
	{
		if (WeaponManager->bIsEquiped)
		{
			bIsAimDownSighs=true;
			
			//PlayMontage(WeaponManager->GetCurrentWeapon()->)
		}
	}
}


void APlayerCharacter::PickUp()
{
	if (!WeaponManager)
		return;
	
	if (bIsOverlappedWeapon&&LastOverlappedWeapon)
	{
		WeaponManager->AddWeapon(LastOverlappedWeapon);
		
		bIsOverlappedWeapon  = false;
		if (LastOverlappedWeapon->Hand_Raise)
		{
			PlayMontage(LastOverlappedWeapon->Hand_Raise);
		}
		//LastOverlappedWeapon = nullptr;
	}
}


void APlayerCharacter::PlayMontage(UAnimMontage* gelenMontage)
{
	if (gelenMontage)
	{
		UAnimInstance* PlayerAnimInstance = MeshHand->GetAnimInstance();
		if (PlayerAnimInstance)
		{
			PlayerAnimInstance->Montage_Play(gelenMontage,1.f);
		}
	}
}

void APlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWeapon* OverlapCast = Cast<AWeapon>(OtherActor);
	if (OverlapCast)
	{
		LastOverlappedWeapon = OverlapCast;
		bIsOverlappedWeapon  = true;
	}
}

void APlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	AWeapon* OverlapCast = Cast<AWeapon>(OtherActor);
	if (OverlapCast)
	{
		LastOverlappedWeapon = nullptr;
		bIsOverlappedWeapon  = false;
	}
}

void APlayerCharacter::AttackStart()
{
	if (!WeaponManager)
		return;
	if (WeaponManager->bIsEquiped)
	{
		WeaponManager->GetCurrentWeapon()->StartFire();
	}
}

void APlayerCharacter::AttackStop()
{
	if (!WeaponManager)
		return;
	
	if (WeaponManager->bIsEquiped)
	{
		WeaponManager->GetCurrentWeapon()->StopFire();
	}
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}