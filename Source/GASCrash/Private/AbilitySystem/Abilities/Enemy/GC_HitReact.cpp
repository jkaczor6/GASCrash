// Copyright Jakub Kaczor


#include "AbilitySystem/Abilities/Enemy/GC_HitReact.h"

void UGC_HitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	
	const FVector AvatarLocation{ GetAvatarActorFromActorInfo()->GetActorLocation() };
	const FVector InstigatorLocation{ Instigator->GetActorLocation() };
	
	ToInstigator = InstigatorLocation - AvatarLocation;
	ToInstigator.Normalize();
}
