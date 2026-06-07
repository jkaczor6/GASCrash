// Copyright Jakub Kaczor


#include "UI/GC_WidgetComponent.h"

#include "AbilitySystem/GC_AbilitySystemComponent.h"
#include "AbilitySystem/GC_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/GC_BaseCharacter.h"
#include "UI/GC_AttributeWidget.h"


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
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair); // for checking the owned widget object
		
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}

void UGC_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject,
	const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	UGC_AttributeWidget* AttributeWidget{ Cast<UGC_AttributeWidget>(WidgetObject) };
	if (!IsValid(AttributeWidget)) return; // only GC Attribute Widgets
	if (!AttributeWidget->MatchesAttributes(Pair)) return; // only matching attributes
	AttributeWidget->AvatarActor = GASCharacter;
		
	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), 0.f); // for initial values
		
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([AttributeWidget, &Pair, this](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), AttributeChangeData.OldValue); // for changes during the game
	});
}