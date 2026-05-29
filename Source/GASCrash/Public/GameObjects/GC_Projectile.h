// Copyright Jakub Kaczor

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GC_Projectile.generated.h"

class UGameplayEffect;
class UProjectileMovementComponent;

UCLASS()
class GASCRASH_API AGC_Projectile : public AActor
{
	GENERATED_BODY()

public:
	AGC_Projectile();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS|Damage", meta = (ExposeOnSpawn, ClampMin = "0.0"))
	float Damage{10.f};
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GAS|Projectile")
	void SpawnImpactEffects();
private:
	
	UPROPERTY(VisibleAnywhere, Category = "GAS|Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(EditDefaultsOnly, Category="GAS|Damage")
	TSubclassOf<UGameplayEffect> DamageEffect;
};
