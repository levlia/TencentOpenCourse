// Copyright Epic Games, Inc. All Rights Reserved.

#include "homework2Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

Ahomework2Projectile::Ahomework2Projectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &Ahomework2Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void Ahomework2Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) 
		&& (OtherComp != nullptr)
		&&OtherComp->ComponentHasTag("CanReactBulletHit")) //&& OtherComp->IsSimulatingPhysics()
		//更改为：具有CanReactBulletHit Tag标签的物体才能对子弹射击产生反应
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * mBulletMass, GetActorLocation());
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		//添加冲量: 大小为质量乘以速度 该工作交给被击中的Character自身来做
		//通过 ShotByBullet function调用
		if (OtherComp->GetOwner()->GetClass()->IsChildOf(AA_Target::StaticClass())) {
			//if this class is target class
			AA_Target* A_ThisTarget = Cast<AA_Target>(OtherComp->GetOwner());
			unsigned int times = 1;
			if (A_ThisTarget->Target_TAG == E_TargetTag::IMPORTANTTARGET_1) {
				times = 2;
			}
			if (A_ThisTarget->Target_TAG == E_TargetTag::WRONGTARGET) {
				Character->PlayerTakeDamage(10);
			}
			else {
				Character->GotScore(times);
			}
			FuncBulletShotBPEvent();

			float ScaleSize = Character->F_HitScale_Y;
			FBulletInfo bulletInfo;
			bulletInfo.BulletDamage = 50;
			bulletInfo.BulletHitLocation = GetActorLocation();
			bulletInfo.BulletVeloc = GetVelocity();
			bulletInfo.BulletMass = mBulletMass;

			A_ThisTarget->ShotByBullet(bulletInfo);

		}

		Destroy();
	}
}

bool Ahomework2Projectile::AssignMater(Ahomework2Character* TargetCharacter)
{
	if (TargetCharacter == nullptr)
	{
		return false;
	} 
	Character = TargetCharacter;
	return true;
}
