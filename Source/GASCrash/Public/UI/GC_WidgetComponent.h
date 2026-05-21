// Copyright Jakub Kaczor

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GC_WidgetComponent.generated.h"


class UAttributeSet;
class UAbilitySystemComponent;
class UGC_AttributeSet;
class UGC_AbilitySystemComponent;
class AGC_BaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GASCRASH_API UGC_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	
	
protected:
	virtual void BeginPlay() override;

private:
	TWeakObjectPtr<AGC_BaseCharacter> GASCharacter;
	TWeakObjectPtr<UGC_AbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UGC_AttributeSet> AttributeSet;
	
	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	
	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);
};
