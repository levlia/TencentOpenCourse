// Fill out your copyright notice in the Description page of Project Settings.

//read Basic GameInfo From file of config files
//userInfo GameSettings etc.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UserInfo.h"
#include <string>

#include "BPFLib_GameInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FUserInfoStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "UserBasicInfo")
	FString UserName;

	UPROPERTY(EditAnywhere, Category = "UserBasicInfo")
	FString Passwd;


	//UFUNCTION(BlueprintCallable, Category = "UserInfoCheck")
	//bool IsEqual(FString InName, FString InPWD) {
	//	return (InName == UserName && InPWD == Passwd);
	//}
};

UCLASS()
class HOMEWORK2_API UBPFLib_GameInfo : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "FStringHelper")
	static bool IsTwoFStringEqual(FString A, FString B) {
		return  A == B;
	}
	
	//UFUNCTION(BlueprintCallable, Category = "UserInfoDataBaseReader")
	//static bool BPFLib_ReadUserInfoFromFile(FString FilePath, FUserInfoStruct& user);
	//
	//static bool BPFLib_ReadUserInfoFromFile(FString FilePath, FUserInfoStruct user);
};
