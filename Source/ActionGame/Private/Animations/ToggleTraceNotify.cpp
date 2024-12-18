// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/ToggleTraceNotify.h"
#include "Combat/TraceComponent.h"

void UToggleTraceNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	UTraceComponent* TraceComp{
		MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>()
	};
	if (!IsValid(TraceComp)) { return; }
	
	TraceComp->bIsAttacking = true;
}

void UToggleTraceNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	UTraceComponent* TraceComp{
		MeshComp->GetOwner()->FindComponentByClass<UTraceComponent>()
	};
	if (!IsValid(TraceComp)) { return; }
	
	TraceComp->bIsAttacking = false;
}
