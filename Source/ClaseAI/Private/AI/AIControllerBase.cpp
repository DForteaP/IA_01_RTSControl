// Fill out your copyright notice in the Description page of Project Settings.


#include "ClaseAI/Public/AI/AIControllerBase.h"

#include "AI/NPCBase.h"
#include "Navigation/PathFollowingComponent.h"


// Sets default values
AAIControllerBase::AAIControllerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//Aqui se garantiza que el personaje esta listo para recibir ordenes
}
void AAIControllerBase::OnUnPossess()
{
	Super::OnUnPossess();
}

void AAIControllerBase::MoveFinished(FAIRequestID FaiRequestID, const FPathFollowingResult& PathFollowingRequestResult) const
{
	GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);
}

void AAIControllerBase::SetMoveCommand(const FVector& Goal)
{
	if (IsCharacterMoving()) return;
	if(GetCharacter())
	{
		FAIMoveRequest MoveRequest;
		MoveRequest
		.SetAcceptanceRadius(50.f)
		.SetCanStrafe(true)
		.SetUsePathfinding(true)
		.SetNavigationFilter(DefaultNavigationFilterClass)
		.SetGoalLocation(Goal);
		
		FNavPathSharedPtr Path;
		FPathFollowingRequestResult RequestID = MoveTo(MoveRequest, &Path);

		GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ThisClass::MoveFinished);
	}
	
}

void AAIControllerBase::SetMoveCommand(const FVector& Goal, bool bAbortMovement)
{
	GetPathFollowingComponent()->AbortMove(*this, FPathFollowingResultFlags::UserAbort);
	SetMoveCommand(Goal);
}

bool AAIControllerBase::IsCharacterMoving() const
{
	const FAIRequestID CurrentID = GetPathFollowingComponent()->GetCurrentRequestId();
	return CurrentID.IsValid();
}

void AAIControllerBase::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
}
