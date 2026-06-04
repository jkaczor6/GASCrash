// Copyright Jakub Kaczor


#include "Utils/GC_BlueprintLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GC_AttributeSet.h"
#include "Characters/GC_BaseCharacter.h"
#include "GameplayTags/GCTags.h"
#include "Kismet/GameplayStatics.h"

EHitDirection UGC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const double Dot{ FVector::DotProduct(TargetForward, ToInstigator) };
	if (Dot < -0.5)
	{
		return EHitDirection::Back;
	}
	if (Dot < 0.5)
	{
		// Either Left or Right
		const FVector Cross{ FVector::CrossProduct(TargetForward, ToInstigator) };
		
		if (Cross.Z < 0.f) { return EHitDirection::Left; }
		
		return EHitDirection::Right;
	}
	return EHitDirection::Forward;
	
}

FName UGC_BlueprintLibrary::GetHitDirectionName(const EHitDirection& HitDirection)
{
	switch (HitDirection)
	{
		case EHitDirection::Back: return FName("Back");
		case EHitDirection::Left: return FName("Left");
		case EHitDirection::Right: return FName("Right");
		case EHitDirection::Forward: return FName("Forward");
		default: return FName("None");
	}
}

FClosestActorWithTagResult UGC_BlueprintLibrary::FindClosestActorWithTag(const UObject* WorldContextObject,
	const FVector& Origin, const FName& Tag)
{
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject, Tag, ActorsWithTag);
	
	double ClosestDistance{ TNumericLimits<double>::Max() };
	AActor* ClosestActor{ nullptr };
	
	for (AActor* Actor : ActorsWithTag)
	{
		if (!IsValid(Actor)) continue;
		AGC_BaseCharacter* BaseCharacter{ Cast<AGC_BaseCharacter>(Actor) };
		if (!IsValid(BaseCharacter) || !BaseCharacter->IsAlive()) continue;
		
		double Distance{ FVector::Dist(Origin, Actor->GetActorLocation()) };
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestActor = Actor;
		}
	}
	
	FClosestActorWithTagResult Result;
	Result.Actor = ClosestActor;
	Result.Distance = ClosestDistance;
	
	return Result;
}

void UGC_BlueprintLibrary::SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect,
	FGameplayEventData& PayLoad, const FGameplayTag& DataTag, float Damage, UObject* OptionalParticleSystem)
{
	AGC_BaseCharacter* BaseCharacter{ Cast<AGC_BaseCharacter>(Target) };
	if (!IsValid(BaseCharacter) || !BaseCharacter->IsAlive()) return;
	
	UGC_AttributeSet* AttributeSet{ Cast<UGC_AttributeSet>(BaseCharacter->GetAttributeSet()) };
	if (!IsValid(AttributeSet)) return;
	
	const bool bLethal{ AttributeSet->GetHealth() - Damage <= 0.f };
	const FGameplayTag EventTag{bLethal ? GCTags::Events::Player::Death : GCTags::Events::Player::HitReact};
	
	PayLoad.OptionalObject = OptionalParticleSystem;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(BaseCharacter, EventTag, PayLoad);
	
	UAbilitySystemComponent* TargetASC{ BaseCharacter->GetAbilitySystemComponent() };
	if (!IsValid(TargetASC)) return;
	
	FGameplayEffectContextHandle ContextHandle{ TargetASC->MakeEffectContext() };
	FGameplayEffectSpecHandle SpecHangle{ TargetASC->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle) };
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHangle, DataTag, -Damage);
	
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHangle.Data.Get());
}
