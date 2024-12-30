// Fill out your copyright notice in the Description page of Project Settings.


#include "A_SpawnTarget.h"


void AA_SpawnTarget::BuildRandomSequence(int low, int high, TArray<int>& RandomArray)
{
	int x = 0, tmp = 0;
	if (low > high) {
		tmp = low;
		low = high;
		high = tmp;
	}
	//TArray<int> RandomArray;
	int mArraySize = high - low + 1;
	RandomArray.Init(0, mArraySize);
	for (int i = low; i <= high; i++) {
		RandomArray[i - low] = i;
	}
	//随机地打乱这mArraySize个数的顺序
	for (int i = mArraySize - 1; i > 0; i--) {
		x = FMath::RandRange(0, i);
		tmp = RandomArray[i];
		RandomArray[i] = RandomArray[x];
		RandomArray[x] = tmp;
	}
	//return RandomArray;
}

// Sets default values
AA_SpawnTarget::AA_SpawnTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AA_SpawnTarget::BeginPlay()
{
	Super::BeginPlay();
	//generate locations from random function in BoundingBox
	FVector FBoundsVector_Box = U_Spawn_Bounds->GetScaledBoxExtent();
	FVector FSpawnOrigin = U_Spawn_Bounds->GetOwner()->GetActorLocation();
	TArray<FTransform> Spawn_Transforms;
	//TArray<E_TargetTag> Spawn_Tags;
	//random SpawnImportantCount important target
	TArray<int> Numbers;
	BuildRandomSequence(0, SpawnCount - 1, Numbers);


	//Positions.Init()
	UE_LOG(LogTemp, Warning, TEXT("random_spawn: Origin: (%f,%f,%f),halfSize:(%f,%f,%f)")
		, FSpawnOrigin.X, FSpawnOrigin.Y, FSpawnOrigin.Z, FBoundsVector_Box.X, FBoundsVector_Box.Y, FBoundsVector_Box.Z);
	
	for (int i = 0; i < int(SpawnCount); i++) {
		FTransform tmpTransForm;
		FRotator tmpRotation = FRotator(0,0,0);
		
		tmpTransForm.SetRotation(tmpRotation.Quaternion());

		FVector Pos_RandomPos = UKismetMathLibrary::RandomPointInBoundingBox(FSpawnOrigin, FBoundsVector_Box);
		tmpTransForm.SetLocation(Pos_RandomPos);

		Spawn_Transforms.Add(tmpTransForm);


		AActor* A_Spawned_Actor = GetWorld()->SpawnActor<AActor>(TargetActorsToSpawn, Pos_RandomPos, tmpRotation);

		if (A_Spawned_Actor->GetClass()->IsChildOf(AA_Target::StaticClass())) {
			AA_Target* tmp=Cast<AA_Target>(A_Spawned_Actor);
			E_TargetTag tmpTag = E_TargetTag::NORMALTARGET;
			//bool B_ShouldBeImportant = false;
			// 
			//Numbers[0]---numbers[SpawnImportantCount-1]是 Important target
			for (int j = 0; j < int(SpawnImportantCount); j++) {

				if (Numbers[j]==i) {
					//B_ShouldBeImportant = true;
					tmpTag = E_TargetTag::IMPORTANTTARGET_1;
					break;
				}
			}
			//numbers[SpawnImportantCount]-----numbers[SpawnImportantCount+SpawnWrongCount-1]是 wrong target
			if (tmpTag == E_TargetTag::NORMALTARGET) {
				for (int j = SpawnImportantCount; j < int(SpawnWrongCount + SpawnWrongCount); j++) {
					if (Numbers[j] == i) {
						//B_ShouldBeImportant = true;
						tmpTag = E_TargetTag::WRONGTARGET;
						break;
					}
				}
			}

			tmp->ChangeTag(tmpTag);
		}
		//GetWorld()->SpawnActorDeferred<AA_Target>(A_Target, tmpTransForm,
		//	ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		

	}
	
}

// Called every frame
void AA_SpawnTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

