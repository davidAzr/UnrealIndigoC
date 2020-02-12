// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyMovement.h"

void UEnemyMovement::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MoveVelocity.ToString())
}