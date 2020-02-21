// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	m_ogLocation = GetActorLocation();
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto runningTime = GetWorld()->GetTimeSeconds();
	auto deltaHeight = (FMath::Sin(GetWorld()->GetTimeSeconds() + DeltaTime) - FMath::Sin(runningTime));
	auto newLocation = GetActorLocation();
	auto newRotation = GetActorRotation();
	newLocation.Z += deltaHeight * m_floatingHeight;
	newRotation.Yaw += DeltaTime * m_rotationRate;
	this->SetActorLocationAndRotation(newLocation, newRotation);
}

bool APowerUp::isValid() const
{
	return m_isValid;
}

