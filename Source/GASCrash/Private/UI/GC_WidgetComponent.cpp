// Copyright Jakub Kaczor


#include "UI/GC_WidgetComponent.h"

#include "AbilitySystem/GC_AbilitySystemComponent.h"
#include "AbilitySystem/GC_AttributeSet.h"
#include "Characters/GC_BaseCharacter.h"


void UGC_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemData();
	
	if (!IsASCInitialized())
	{
		GASCharacter->OnASCInitialized.AddDynamic(this, &UGC_WidgetComponent::OnASCInitialized);
		return;
	}
	
	InitializedAttributesDelegate();
}

void UGC_WidgetComponent::InitAbilitySystemData()
{
	GASCharacter = Cast<AGC_BaseCharacter>(GetOwner());
	AttributeSet = Cast<UGC_AttributeSet>(GASCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UGC_AbilitySystemComponent>(GASCharacter->GetAbilitySystemComponent());
}

bool UGC_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UGC_WidgetComponent::InitializedAttributesDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributesInitialized.AddDynamic(this, &UGC_WidgetComponent::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void UGC_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UGC_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<UGC_AttributeSet>(AS);
	
	if (!IsASCInitialized()) return;
	InitializedAttributesDelegate();
}

void UGC_WidgetComponent::BindToAttributeChanges()
{
	// TODO: Listen for changes to Gameplay Attributes and update our widgets accordingly
}
