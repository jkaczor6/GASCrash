// Copyright Jakub Kaczor


#include "GameObjects/GC_Projectile.h"

#include "AbilitySystemComponent.h"
#include "Characters/GC_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"


AGC_Projectile::AGC_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	
	bReplicates = true;
}

void AGC_Projectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	AGC_PlayerCharacter* PlayerCharacter{ Cast<AGC_PlayerCharacter>(OtherActor) };
	if (!IsValid(PlayerCharacter)) return;
	if (!PlayerCharacter->IsAlive()) return;
	UAbilitySystemComponent* ASC{ PlayerCharacter->GetAbilitySystemComponent() };
	if (!IsValid(ASC) || !HasAuthority()) return;
	
	FGameplayEffectContextHandle ContextHandle{ ASC->MakeEffectContext() };
	FGameplayEffectSpecHandle SpecHandle{ ASC->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle) };
	
	// TODO: use the damage variable for the amount of damage to cause.
	
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
	SpawnImpactEffects();
	Destroy();
}
