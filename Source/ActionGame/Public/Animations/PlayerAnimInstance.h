// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentSpeed{0.0f};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PlayerMovingDirection{0.0f};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsinAir{false};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInCombat{false};

	UFUNCTION(BlueprintCallable)
	void UpdateSpeed();

	UFUNCTION(BlueprintCallable)
	void CheckIsJumping();

public:
	UFUNCTION(BlueprintCallable)
	void HandleUpdatedTarget(AActor* NewTargetActorRef);
	
	UFUNCTION(BlueprintCallable)
	void UpdateDirection();
};
