// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BPFLib_GameInfo.h"

#include "FPSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class HOMEWORK2_API UFPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	TArray<FUserInfoStruct> FPSUsers;
	
	
};
