// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "TP_WeaponComponent.h"

#include "Kismet/KismetSystemLibrary.h"

#include "Logging/LogMacros.h"
#include "homework2Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class Ahomework2Character : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
public:
	Ahomework2Character();

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	UFUNCTION(BlueprintImplementableEvent, Category = "StaticEvent")
	void FuncGotAttackBPEvent();
	
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, Category = Input)
	bool HasWeap = false;
	UPROPERTY(EditAnywhere, Category = Input)
	float Score = 0;

	UPROPERTY(VisibleAnywhere, Category = Property)
	float  HP= 100;

	/** 响应要更新的武器状态、得分(生命值)。修改后，立即在服务器上调用，并在客户端上调用以响应RepNotify*/
	void OnWeaponUpdate();
	//void OnScoreUpdate();

	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	//UFUNCTION(BlueprintCallable, Category = "GameInfo")
	bool TakeDamage(float damage) {
		if ((HP - damage) >= 0) {
			HP -= damage;
			FuncGotAttackBPEvent();
			return true;
		}
		return false;
	}


	//自定义简易Player的状态 0:game not started 1:game started 2:game end
	UPROPERTY(EditAnywhere, Category = State)
	int SimplePlayerState = 0;

	UPROPERTY(EditAnywhere, Category = Input)
	float F_ScoreAdder_X = 2;
	UPROPERTY(EditAnywhere, Category = Input)
	float F_HitScale_Y = 0.5;
	UPROPERTY(EditAnywhere, Category = Input)
	float GameTime = 30;

	void GotScore(unsigned int Times);
	//void GotWeapon();
	//void ScorePlus();

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	float GetScore() {
		return Score;
	}

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	int GetSimplePlayerState() {
		return SimplePlayerState;
	}

	UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
	bool SetSimplePlayerState(int i) {
		if (i >= 0 && i <= 2) {
			SimplePlayerState = i;
			return true;
		}
		return false;
	}

	UFUNCTION(BlueprintCallable, Category = "GameInfo")
	float GetLeftTime() {
		return GameTime;
	}

	UFUNCTION(BlueprintCallable, Category = "GameInfo")
	float GetScoreAdderX() {
		return F_ScoreAdder_X;
	}

	UFUNCTION(BlueprintCallable, Category = "GameInfo")
	float GetScaleY () {
		return F_HitScale_Y;
	}

	UFUNCTION(BlueprintCallable, Category = "GameInfo")
	float GetHP() {
		return HP;
	}

	UFUNCTION(BlueprintCallable, Category = "WeponInfo")
	bool GetWeaponInfor(int weaponIndex, int& LeftBulletCount, int& TotalBulletCount);
	//UFUNCTION(BlueprintCallable, Category = "MapInfo")
	//int GetTotalScore() {
	//	return TotalScore;
	//}

	//UFUNCTION(BlueprintCallable, Category = "MapInfo")
	//bool SetTotalScore(int BPTotalScore) {
	//	bool isSuccess = false;
	//	TotalScore = BPTotalScore;
	//	isSuccess = true;
	//	return isSuccess;
	//}

};

