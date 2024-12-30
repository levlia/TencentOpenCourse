// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Target.generated.h"

UENUM()
enum class E_TargetTag:uint8
{
	NORMALTARGET,IMPORTANTTARGET_1,WRONGTARGET
	//»÷ÖÐWrongTarget»á¼õÉÙ10µÎHP
};

UCLASS()
class HOMEWORK2_API AA_Target : public AActor
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool B_HasBeenShot = false;

	UPROPERTY(EditAnywhere, Category = Input)
	E_TargetTag Target_TAG = E_TargetTag::NORMALTARGET;
	
	UFUNCTION(BlueprintCallable)
	E_TargetTag GetTag() {
		return Target_TAG;
	}

};
