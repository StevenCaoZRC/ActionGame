// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/LockonComponent.h"

#include "HeadMountedDisplayTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/Enemy.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
ULockonComponent::ULockonComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

// Called when the game starts
void ULockonComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerRef = GetOwner<ACharacter>();
	ControllerRef = GetWorld()->GetFirstPlayerController();
	MovementComponentRef = OwnerRef->GetCharacterMovement();
	SpringArmRef = OwnerRef->FindComponentByClass<USpringArmComponent>();
	// ...
	
}

void ULockonComponent::StartLockon(float Radius)
{
	FHitResult OutResult; 
	FVector CurrentLocation{ OwnerRef->GetActorLocation() };
	FCollisionShape Sphere{ FCollisionShape::MakeSphere(Radius) };
	FCollisionQueryParams IgnoreParams{
		FName(TEXT("Ignore Collision Params")),
		false,
		OwnerRef
	};
	bool bHasFoundTarget { GetWorld()->SweepSingleByChannel(
		OutResult,
		CurrentLocation,
		CurrentLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		Sphere,
		IgnoreParams
		) };
	
	if (!bHasFoundTarget) { return; }

	if (!OutResult.GetActor()->Implements<UEnemy>()) { return; }
	
	ControllerRef->SetIgnoreLookInput(true);
	MovementComponentRef->bOrientRotationToMovement = false;
	MovementComponentRef->bUseControllerDesiredRotation = true;
	CurrentTargetActor = OutResult.GetActor();

	SpringArmRef->TargetOffset = FVector{0.0f, 0.0f, 100.0f};

	IEnemy::Execute_OnSelect(CurrentTargetActor);
	
	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::EndLockon()
{
	IEnemy::Execute_OnDeselect(CurrentTargetActor);
	CurrentTargetActor = nullptr;
	
	MovementComponentRef->bOrientRotationToMovement = true;
	MovementComponentRef->bUseControllerDesiredRotation = false;
	SpringArmRef->TargetOffset = FVector::ZeroVector;
	
	ControllerRef->ResetIgnoreLookInput();

	OnUpdatedTargetDelegate.Broadcast(CurrentTargetActor);
}

void ULockonComponent::ToggleLockon(float Radius)
{
	if (IsValid(CurrentTargetActor))
	{
		EndLockon();
	}
	else
	{
		StartLockon(Radius);
	}
}

// Called every frame
void ULockonComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!IsValid(CurrentTargetActor)) { return; }
	
	FVector CurrentLocation{ OwnerRef->GetActorLocation() };
	FVector TargetLocation{ CurrentTargetActor->GetActorLocation() };
	double DistanceToTarget {
		FVector::Distance(CurrentLocation, TargetLocation)
	};
	if (DistanceToTarget >= BreakDistance)
	{
		EndLockon();
		return;
	}
	
	TargetLocation.Z -= 125.0f;
	
	FRotator NewRotation{ UKismetMathLibrary::FindLookAtRotation(
		CurrentLocation,TargetLocation
		) };
	
	ControllerRef->SetControlRotation(NewRotation);
	
	// ...
}

