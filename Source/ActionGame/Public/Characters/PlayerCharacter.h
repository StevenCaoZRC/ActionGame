// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/MainPlayer.h"
#include "Interfaces/Fighter.h"
#include "PlayerCharacter.generated.h"


UCLASS()
class ACTIONGAME_API APlayerCharacter : public ACharacter, public IMainPlayer, public IFighter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UStatsComponent* StatsComponent;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class ULockonComponent* LockonComponent;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UCombatComponent* CombatComponent;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UTraceComponent* TraceComponent;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UBlockComponent* BlockComponent;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	class UPlayerActionsComponent* PlayerActionsComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UPlayerAnimInstance* PlayerAnim;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float GetDamage() override;
};
