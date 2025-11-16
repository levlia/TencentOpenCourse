// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Target.h"


// Sets default values
AA_Target::AA_Target()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//USM_Target = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Super Mesh"));
	//const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("D:/UnrealProjects/TencentOpenClass/homework2/Content/LevelPrototyping/Meshes/SM_ChamferCube.uasset"));
	//USM_Target->SetStaticMesh(MeshObj.Object);
}

void AA_Target::ChangeTag(E_TargetTag NewTag)
{
	Target_TAG = NewTag;
	
}

// Called when the game starts or when spawned
void AA_Target::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AA_Target::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_Target::ShotByBullet(FBulletInfo Bullet)
{

	float HPLost = Bullet.BulletDamage;
	if (HP - HPLost >= 0) {
		HP -= HPLost;
	}
	else {
		HP = 0;
	}
	if (!B_HasBeenShot) {
		//SetWorldScale3D(FVector3d(F_HitScale_Y, F_HitScale_Y, F_HitScale_Y));
		B_HasBeenShot = true;
		/*FVector2D MovementVector = FVector2D(1.0, 1.0);
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);*/
		TArray<USkeletalMeshComponent*> TargetSkeletalMeshComponents;
		this->GetComponents(TargetSkeletalMeshComponents);
		int SkeletalMeshCount = TargetSkeletalMeshComponents.Num();
		for (int i = 0; i < SkeletalMeshCount; i++) {

			TargetSkeletalMeshComponents[i]->AddImpulseAtLocation(Bullet.BulletVeloc * Bullet.BulletMass, Bullet.BulletHitLocation);

		}
	}
	else {
		TArray<USkeletalMeshComponent*> TargetSkeletalMeshComponents;
		this->GetComponents(TargetSkeletalMeshComponents);
		int SkeletalMeshCount = TargetSkeletalMeshComponents.Num();
		for (int i = 0; i < SkeletalMeshCount; i++) {
			TargetSkeletalMeshComponents[i]->AddImpulseAtLocation(Bullet.BulletVeloc * Bullet.BulletMass, Bullet.BulletHitLocation);
			//TargetSkeletalMeshComponents[i]->IsPhysicsCollisionEnabled();
			//TargetSkeletalMeshComponents[i]->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
		}

		this->Destroy();
	}


}

