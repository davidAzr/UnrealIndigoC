// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnemyMovement.generated.h"

/**
 * 
 */
UCLASS()
class UNREALINDIGOC_API UEnemyMovement : public UFloatingPawnMovement
{
	GENERATED_BODY()
	
public:
	virtual void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;
	
	
	
};
