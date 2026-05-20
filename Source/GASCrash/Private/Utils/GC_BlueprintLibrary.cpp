// Copyright Jakub Kaczor


#include "Utils/GC_BlueprintLibrary.h"

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
