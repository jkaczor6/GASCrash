// Copyright Jakub Kaczor


#include "GASCrash/Public/Characters/GC_BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "Virtualization/VirtualizationSystem.h"

AGC_BaseCharacter::AGC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* AGC_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AGC_BaseCharacter::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec{ FGameplayAbilitySpec(Ability) };
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void AGC_BaseCharacter::InitializeAttributes() const
{
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect not set."));
	
	FGameplayEffectContextHandle ContextHandle{ GetAbilitySystemComponent()->MakeEffectContext() };
	FGameplayEffectSpecHandle SpecHandle{ GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect, 1.f, ContextHandle) };
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
