// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPCBase.generated.h"

class AAIControllerBase;

UCLASS()
class CLASEAI_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

public:

	ANPCBase();

	UPROPERTY(EditInstanceOnly)
	AActor* ReferenceActor;
	
protected:

	virtual void BeginPlay() override;

};
