// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/PlayerAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/PawnMovementComponent.h"


void UPlayerAnimInstance::UpdateSpeed()
{
	APawn* PawnRef{TryGetPawnOwner()};
	if (!IsValid(PawnRef)) { return; }
	FVector Velocity{PawnRef->GetVelocity()};
	CurrentSpeed = static_cast<float>(Velocity.Length()); 
}

void UPlayerAnimInstance::UpdateDirection()
{
	APawn* PawnRef{TryGetPawnOwner()};
	if (!IsValid(PawnRef)) { return; }
	if (!bIsInCombat) { return; } 
	PlayerMovingDirection = UKismetAnimationLibrary::CalculateDirection(
													PawnRef->GetVelocity(),
													PawnRef->GetActorRotation());
}

void UPlayerAnimInstance::CheckIsJumping()
{
	APawn* PawnRef{TryGetPawnOwner()};
	if (!IsValid(PawnRef)) { return; }
	bIsinAir = PawnRef->GetMovementComponent()->IsFalling();
}

void UPlayerAnimInstance::HandleUpdatedTarget(AActor* NewTargetActorRef)
{
	bIsInCombat = IsValid(NewTargetActorRef);
}
