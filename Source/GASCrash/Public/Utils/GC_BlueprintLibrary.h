// Copyright Jakub Kaczor

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GC_BlueprintLibrary.generated.h"

struct FGameplayTag;
struct FGameplayEventData;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Left,
	Right,
	Forward,
	Back
};

USTRUCT(BlueprintType)
struct FClosestActorWithTagResult
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AActor> Actor;
	
	UPROPERTY(BlueprintReadWrite)
	float Distance{ 0.f };
};

UCLASS()
class GASCRASH_API UGC_BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure)
	static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);
	
	UFUNCTION(BlueprintPure)
	static FName GetHitDirectionName(const EHitDirection& HitDirection);
	
	UFUNCTION(BlueprintCallable)
	static FClosestActorWithTagResult FindClosestActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag);
	
	UFUNCTION(BlueprintCallable)
	static void SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect, UPARAM(ref) FGameplayEventData& PayLoad, const FGameplayTag & DataTag, float Damage, UObject* OptionalParticleSystem = nullptr);
	
	UFUNCTION(BlueprintCallable, Category="GAS|Abilities")
	static TArray<AActor*> HitBoxOverlapTest(AActor* AvatarActor, float HitBoxRadius, float HitBoxForwardOffset = 0.f, float HitBoxElevationOffset = 0.f, bool bDrawDebugs = false);
	
	static void DrawHitBoxOverlapDebugs(const UObject* WorldContextObject, float HitBoxRadius, const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation);
	
	UFUNCTION(BlueprintCallable, Category="GAS|Abilities")
	static TArray<AActor*> ApplyKnockback(AActor* AvatarActor, const TArray<AActor*>& HitActors, float InnerRadius, float OuterRadius, float LaunchForceMagnitude, float RotationAngle = 45.f, bool bDrawDebugs = false);
};
