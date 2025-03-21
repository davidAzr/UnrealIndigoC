// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealIndigoCCharacter.h"
#include "IndigoCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDead, float, time);

/**
 * 
 */
UCLASS()
class UNREALINDIGOC_API AIndigoCharacter : public AUnrealIndigoCCharacter
{
	GENERATED_BODY()

	AIndigoCharacter();
	
public:
	UFUNCTION(BlueprintCallable)
	void Shoot();

	void RecieveDamage(float damage);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerDead PlayerDie;

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float m_maxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float m_attackRate = 0.25f;

	float m_currentHealth;

	TSubclassOf<class AProjectile> m_currentProjectileType;
	
	float m_lastAttackTime;
};
