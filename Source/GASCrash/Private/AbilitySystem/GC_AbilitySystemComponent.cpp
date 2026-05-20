// Copyright Jakub Kaczor


#include "AbilitySystem/GC_AbilitySystemComponent.h"


UGC_AbilitySystemComponent::UGC_AbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UGC_AbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UGC_AbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

