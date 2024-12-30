// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "GameFramework/Actor.h"

#include "UserInfo.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class HOMEWORK2_API UUserInfo : public UObject
{
	GENERATED_BODY()
public:

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
	//bool BPFLib_ReadUserInfoFromFile(FString FilePath);

};
