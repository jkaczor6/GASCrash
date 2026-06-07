// Copyright Jakub Kaczor


#include "Characters/GC_EnemyCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GC_AbilitySystemComponent.h"
#include "AbilitySystem/GC_AttributeSet.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "GameplayTags/GCTags.h"
#include "Net/UnrealNetwork.h"

AGC_EnemyCharacter::AGC_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UGC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UGC_AttributeSet>("AttributeSet");
}

void AGC_EnemyCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, bIsBeingLaunched);
}

UAbilitySystemComponent* AGC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AGC_EnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void AGC_EnemyCharacter::StopMovementUntilLanded()
{
	bIsBeingLaunched = true;
	AAIController* AIC = GetController<AAIController>();
	if (!IsValid(AIC)) return;
	AIC->StopMovement();
	if (!LandedDelegate.IsAlreadyBound(this, &ThisClass::EnableMovementOnLanded))
	{
		LandedDelegate.AddDynamic(this, &ThisClass::EnableMovementOnLanded);
	}
}

void AGC_EnemyCharacter::EnableMovementOnLanded(const FHitResult& Hit)
{
	bIsBeingLaunched = false;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GCTags::Events::Enemy::EndAttack, FGameplayEventData());
	LandedDelegate.RemoveAll(this);
}

void AGC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	if (!HasAuthority()) return;
	
	GiveStartupAbilities();
	InitializeAttributes();
	
	UGC_AttributeSet* GC_AS = Cast<UGC_AttributeSet>(GetAttributeSet());
	if (!IsValid(GC_AS)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GC_AS->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

void AGC_EnemyCharacter::HandleDeath()
{
	Super::HandleDeath();
	
	AAIController* AIC = GetController<AAIController>();
	if (!IsValid(AIC)) return;
	AIC->StopMovement();
}

