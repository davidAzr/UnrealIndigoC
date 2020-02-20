// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraRegion.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Level/EnemySpawnController.h"
#include "GameFramework/PlayerController.h"
#include "Level/EnemySpawner.h"

// Sets default values
ACameraRegion::ACameraRegion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	////auto defaultScene = CreateDefaultSubobject<USceneComponent>("root");
	m_triggerVolume = CreateDefaultSubobject<UBoxComponent>("Region Volume");
	m_triggerVolume->SetupAttachment(RootComponent);
	m_cameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	
	FAttachmentTransformRules attachmentRules(EAttachmentRule::KeepRelative, true);
	m_cameraComponent->AttachToComponent(RootComponent, attachmentRules);

	m_spawnController = CreateDefaultSubobject<UEnemySpawnController>("Spawn Controller");
	m_spawnController->SetCameraRegion(this);

	m_isActiveRegion = false;
}

bool ACameraRegion::GetIsActiveCameraRegion()
{
	return m_isActiveRegion;
}

// Called when the game starts or when spawned
void ACameraRegion::BeginPlay()
{
	Super::BeginPlay();
	m_triggerVolume->SetGenerateOverlapEvents(true);
	m_triggerVolume->SetVisibility(false);

	if (m_isFirstRegion) {
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this, 0.5, EViewTargetBlendFunction::VTBlend_Cubic);
		m_isActiveRegion = true;
		if (m_spawnController) {
			m_spawnController->StartSpawning();
		}
	}

	// Event Binding
	m_triggerVolume->OnComponentEndOverlap.AddDynamic(this, &ACameraRegion::OnEndOverlap);
	m_triggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACameraRegion::OnBeginOverlap);
}

// When an actor enters the camera region we check if it is the player actor
// and if it is we change the camera to the one of this region
void ACameraRegion::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn()) {
		UE_LOG(LogTemp, Warning, TEXT("ACTOR ENTERS REGION"))
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this, 0.5, EViewTargetBlendFunction::VTBlend_Cubic);
		m_isActiveRegion = true;
		if (m_spawnController) {
			m_spawnController->StartSpawning();
		}
	}
}

void ACameraRegion::OnEndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn()) {
		UE_LOG(LogTemp, Warning, TEXT("ACTOR LEAVES REGION"))
		m_isActiveRegion = false;
		if (m_spawnController) {
			m_spawnController->StopSpawning();
		}
	}
}

// Called every frame
void ACameraRegion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACameraRegion::AddSpawnToController(AEnemySpawner * enemySpawner)
{
	m_spawnController->AddEnemySpawn(enemySpawner);
}

void ACameraRegion::DecreaseEnemyCount()
{
	m_spawnController->DecreaseEnemyCount();
}
