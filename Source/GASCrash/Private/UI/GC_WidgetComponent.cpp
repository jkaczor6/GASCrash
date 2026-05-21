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
	};
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

void UGC_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UGC_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<UGC_AttributeSet>(AS);
	
	// TODO: Check if the Attribute Set has been initialized with the first GE
	// If not, bind to some delegate that will be broadcast when it is initialized
}
