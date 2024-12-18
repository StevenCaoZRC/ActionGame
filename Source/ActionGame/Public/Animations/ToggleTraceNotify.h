// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ToggleTraceNotify.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONGAME_API UToggleTraceNotify : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		float TotalDuration,
		const FAnimNotifyEventReference& EventReference
		) override;

	UFUNCTION(BlueprintCallable)
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference
		) override;
};
