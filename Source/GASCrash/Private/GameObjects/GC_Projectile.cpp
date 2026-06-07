// Copyright Jakub Kaczor


#include "GameObjects/GC_Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Characters/GC_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayTags/GCTags.h"
#include "Utils/GC_BlueprintLibrary.h"


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
	
	FGameplayEventData Payload;
	Payload.Instigator = GetOwner();
	Payload.Target = PlayerCharacter;
	
	UGC_BlueprintLibrary::SendDamageEventToPlayer(PlayerCharacter,DamageEffect, Payload, GCTags::SetByCaller::Projectile, Damage, GCTags::None);
	
	SpawnImpactEffects();
	Destroy();
}
