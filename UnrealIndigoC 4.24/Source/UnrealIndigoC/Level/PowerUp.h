 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

UCLASS()
class UNREALINDIGOC_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* m_mesh;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	bool m_isValid = true;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	float m_floatingHeight = 30.f;

	UPROPERTY(EditAnywhere, Category = "Configuration")
	float m_rotationRate = 20.f;

	FVector m_ogLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool isValid() const;

};
