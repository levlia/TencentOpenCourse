// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorUserInfo.h"


// Sets default values
AActorUserInfo::AActorUserInfo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorUserInfo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorUserInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

