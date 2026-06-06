// Copyright Jakub Kaczor

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GC_GameplayAbility.h"
#include "GC_Primary.generated.h"

UCLASS()
class GASCRASH_API UGC_Primary : public UGC_GameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category="GAS|Abilities")
	void SendHitReactEventToActors(const TArray<AActor*>& ActorsHit);
	
protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS|Abilities")
	float HitBoxRadius{ 100.f };
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS|Abilities")
	float HitBoxForwardOffset{ 200.f };
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="GAS|Abilities")
	float HitBoxElevationOffset{ 20.f };
};
