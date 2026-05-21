// Copyright Jakub Kaczor

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GC_AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "GC_AttributeWidget.generated.h"


UCLASS()
class GASCRASH_API UGC_AttributeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Attributes")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS|Attributes")
	FGameplayAttribute MaxAttribute;
	
	void OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UGC_AttributeSet* AttributeSet);
	bool MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Change"))
	void BP_OnAttributeChange(float NewValue, float NewMaxValue);
};
