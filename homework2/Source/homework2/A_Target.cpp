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

