// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

UCLASS()
class CLASEAI_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAIControllerBase();

	void SetMoveCommand(const FVector& Goal);
	void SetMoveCommand(const FVector& Goal, bool bAbortMovement);
	bool IsCharacterMoving() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
	void MoveFinished(FAIRequestID FaiRequestID, const FPathFollowingResult& PathFollowingRequestResult) const;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
