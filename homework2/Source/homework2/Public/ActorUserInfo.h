// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorUserInfo.generated.h"

UCLASS()
class HOMEWORK2_API AActorUserInfo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorUserInfo();

	UPROPERTY(EditAnywhere, Category = "UserBasicInfo")
	FString UsrName;

	UPROPERTY(EditAnywhere, Category = "UserBasicInfo")
	FString UsrPasswd;


	UFUNCTION(BlueprintCallable, Category = "UserInfoFunc")
	void SetUserName(FString UserName) {
		UsrName = UserName;
	}

	UFUNCTION(BlueprintCallable, Category = "UserInfoFunc")
	void SetPasswd(FString UserPasswd) {
		UsrPasswd = UserPasswd;
	}

	UFUNCTION(BlueprintCallable, Category = "UserInfoFunc")
	bool BCheckIsPairMatch(FString NAME, FString PWD) {
		return (NAME == UsrName && PWD == UsrPasswd);
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
