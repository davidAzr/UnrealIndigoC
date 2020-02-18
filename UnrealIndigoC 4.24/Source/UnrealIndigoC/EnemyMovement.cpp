// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyMovement.h"
#include "GameFramework/Pawn.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"

void UEnemyMovement::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {

	auto newVelocity = MoveVelocity;
	auto StartRot = UpdatedComponent->GetComponentRotation();
	auto TargetRot = (newVelocity * -1).Rotation();
	auto Speed = 3.f;

	UpdatedComponent->GetOwner()->SetActorRotation(FMath::RInterpTo(StartRot, TargetRot, GetWorld()->GetDeltaSeconds(), Speed));
	Velocity = MoveVelocity;
}