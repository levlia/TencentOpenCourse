// Copyright Epic Games, Inc. All Rights Reserved.

#include "homework2Character.h"
#include "TP_WeaponComponent.h"
#include "homework2Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"



DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// Ahomework2Character

Ahomework2Character::Ahomework2Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void Ahomework2Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void Ahomework2Character::Tick(float DeltaSeconds)
{
	//
	Super::Tick(DeltaSeconds);
	int i = 0;
	//UTP_WeaponComponent thisWeapon;
	if (this->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>()) {
		//查询是否有武器
		//若有武器
		i++;
	}
	
	if (SimplePlayerState == 1) {
		GameTime -= DeltaSeconds;
		//TakeDamage(DeltaSeconds);
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void Ahomework2Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &Ahomework2Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &Ahomework2Character::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void Ahomework2Character::OnWeaponUpdate()
{
	//客户端特定的功能
	if (IsLocallyControlled())
	{
		FString healthMessage = FString::Printf(TEXT("You now have weapon remaining."));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);

		//if (CurrentHealth <= 0)
		//{
		//	FString deathMessage = FString::Printf(TEXT("You have been killed."));
		//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, deathMessage);
		//}
	}

	//服务器特定的功能
	if (GetLocalRole() == ROLE_Authority)
	{
		FString healthMessage = FString::Printf(TEXT("%s now has weapon s."), *GetFName().ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, healthMessage);
	}

	//在所有机器上都执行的函数。
	/*
		因任何因伤害或死亡而产生的特殊功能都应放在这里。
	*/
}

void Ahomework2Character::GotScore(unsigned int Times)
{
	Score += F_ScoreAdder_X * Times;
}

bool Ahomework2Character::GetWeaponInfor(int weaponIndex, int& LeftBulletCount, int& TotalBulletCount)
{
	//0<=weaponIndex<weaponCount
	LeftBulletCount = 0;
	TotalBulletCount = 30;
	//this->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>();
	int WeaponCount = this->GetInstanceComponents().Num();
	if (weaponIndex < 0 || weaponIndex >= WeaponCount) {
		return false;
	}
	int startIndex = 0;
	int Index = 0;
	for (int i = 0; i <= weaponIndex; i++) {
		//find i-th weapon
		UTP_WeaponComponent* thisWeapon = nullptr;
		bool BIsFindIthWeapon = this->GetInstanceComponents().FindItemByClass<UTP_WeaponComponent>(&thisWeapon, &Index, startIndex);
		if (BIsFindIthWeapon) {
			startIndex = Index + 1;
			if (i == weaponIndex) {
				//找到了第weaponIndex个武器
				LeftBulletCount = thisWeapon->GetCurBulletCount();
				TotalBulletCount = thisWeapon->GetTotalBulletCount();
				return true;
			}
		}
	}

	return false;
}

//void Ahomework2Character::GotWeapon()
//{
//	this->HasWeap = true;
//}
//
//void Ahomework2Character::ScorePlus()
//{
//	this->Score++;
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Score = %d."),Score));
//	//UE_LOG(LogTemp, Warning, TEXT("your current score %d"),Score);
//}


void Ahomework2Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void Ahomework2Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}