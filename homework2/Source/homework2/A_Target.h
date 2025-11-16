// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "A_Target.generated.h"

UENUM()
enum class E_TargetTag:uint8
{
	NORMALTARGET,IMPORTANTTARGET_1,WRONGTARGET
	//击中WrongTarget会减少10滴HP
};
USTRUCT()
struct FBulletInfo
{
	GENERATED_BODY()
//定义击中该目标的子弹的信息，后续可能能用，子弹Onhit函数里，生成该BulletInfo的实例传给targetGotShot函数
	float BulletDamage;

	float BulletMass;

	FVector BulletVeloc;

	FVector BulletHitLocation;

};

UCLASS()
class HOMEWORK2_API AA_Target : public ACharacter
{
	GENERATED_BODY()
	
public:	
	//UPROPERTY(EditAnywhere, Category = "TargetParam|StaticMesh")
	//UStaticMeshComponent* USM_Target;

	// Sets default values for this actor's properties
	AA_Target();

	void ChangeTag(E_TargetTag NewTag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool B_HasBeenShot = false;

	float HP = 100;

	float F_HitScale_Y = 0.5;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Input)
	E_TargetTag Target_TAG = E_TargetTag::NORMALTARGET;

	void ShotByBullet(FBulletInfo Bullet);
	
	UFUNCTION(BlueprintCallable)
	E_TargetTag GetTag() {
		return Target_TAG;
	}

};
