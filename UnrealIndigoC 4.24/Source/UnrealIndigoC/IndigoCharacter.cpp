// Fill out your copyright notice in the Description page of Project Settings.

#include "IndigoCharacter.h"
#include "Projectile.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"

AIndigoCharacter::AIndigoCharacter() {
	
	static ConstructorHelpers::FClassFinder<AProjectile> ClassFinder(TEXT("Blueprint'/Game/IndigoGame/BP_IndigoProjectile.BP_IndigoProjectile_C'"));
	if (ClassFinder.Class)
		m_currentProjectileType = ClassFinder.Class;

	m_currentHealth = m_maxHealth;
}

void AIndigoCharacter::Shoot()
{
	FActorSpawnParameters spawnParameters;
	auto currentTime = GetWorld()->GetTimeSeconds();
	if (currentTime - m_lastAttackTime >= m_attackRate) {
		m_lastAttackTime = currentTime;
		auto bulletStart = GetMesh()->GetSocketTransform("ProjectileSocket");
		GetWorld()->SpawnActor<AProjectile>(m_currentProjectileType, bulletStart.GetLocation(), bulletStart.GetRotation().Rotator(), spawnParameters);
	}

}

void AIndigoCharacter::RecieveDamage(float damage)
{
	m_currentHealth -= damage;
	if (m_currentHealth <= 0) {
		PlayerDie.Broadcast(GetWorld()->GetTimeSeconds());
	}
}

float AIndigoCharacter::GetCurrentHealth() const
{
	return m_currentHealth;
}

