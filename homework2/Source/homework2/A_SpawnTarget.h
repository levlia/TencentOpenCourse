// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"


#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "A_Target.h"

#include "A_SpawnTarget.generated.h"

UCLASS()
class HOMEWORK2_API AA_SpawnTarget : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, Category = "SpawnParam|SpawnBounding|Box")
	class UBoxComponent* U_Spawn_Bounds;

	UPROPERTY(EditAnywhere, Category = "SpawnParam|count")
	unsigned int SpawnCount = 2;
	UPROPERTY(EditAnywhere, Category = "SpawnParam|count")
	unsigned int SpawnImportantCount = 0;
	UPROPERTY(EditAnywhere, Category = "SpawnParam|count")
	unsigned int SpawnWrongCount = 0;

	//generate random serial numbers length is high-low+1
	void BuildRandomSequence(int low, int high, TArray<int>& RandomArray);

	// Sets default values for this actor's properties
	AA_SpawnTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere,meta = (AllowPrivateAccess="true"),Category = "SpawnParam|Class")
	TSubclassOf<AActor> TargetActorsToSpawn;

};
