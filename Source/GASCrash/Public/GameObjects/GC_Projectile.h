// Copyright Jakub Kaczor

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GC_Projectile.generated.h"

UCLASS()
class GASCRASH_API AGC_Projectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGC_Projectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
