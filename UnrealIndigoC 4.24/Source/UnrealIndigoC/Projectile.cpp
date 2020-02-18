// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("Bullet Mesh");
	m_movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Bullet Movement Component");
	SetRootComponent(m_mesh);
	UE_LOG(LogTemp, Warning, TEXT("Constructor projectile"))
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	m_mesh->SetNotifyRigidBodyCollision(true);

	UE_LOG(LogTemp, Warning, TEXT("Binding Events"))
	// Event Binding
	m_mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	m_mesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
	if (OtherActor && (OtherActor != this))
	{
		auto hitActor = dynamic_cast<AEnemy*>(OtherActor);
		if (hitActor != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Enemy HIT"))
			hitActor->RecieveDamage(25.f);
		}
	}
}


void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy OVERLAP"))
		if (auto hitActor = dynamic_cast<AEnemy*>(OtherActor) != nullptr)
		{
		}
	}
}


