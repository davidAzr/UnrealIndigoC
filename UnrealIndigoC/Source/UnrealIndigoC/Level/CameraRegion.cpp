// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraRegion.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ACameraRegion::ACameraRegion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		UE_LOG(LogTemp, Warning, TEXT("Actor begin overlap"))

	m_triggerVolume = CreateDefaultSubobject<UBoxComponent>("Region Volume");
	m_triggerVolume->SetGenerateOverlapEvents(true);
	m_triggerVolume->SetVisibility(false);
	this->SetRootComponent(m_triggerVolume);
	m_cameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");

	FAttachmentTransformRules attachmentRules(EAttachmentRule::KeepRelative, true);
	m_cameraComponent->AttachToComponent(m_triggerVolume, attachmentRules);

	// Event Binding
	m_triggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ACameraRegion::OnBeginOverlap);
}

// Called when the game starts or when spawned
void ACameraRegion::BeginPlay()
{
	Super::BeginPlay();
	
}

// When an actor enters the camera region we check if it is the player actor
// and if it is we change the camera to the one of this region
void ACameraRegion::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn()) {
		GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this, 0.5, EViewTargetBlendFunction::VTBlend_Cubic);
	}
}

// Called every frame
void ACameraRegion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

